//
//  main.cpp
//  png2c
//
//  Created by Magnus Runesson on 01/12/15.
//  Copyright (c) 2015 Pokewhat. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>

typedef struct
{
	unsigned short w;
	unsigned short h;
	unsigned short* pixels;
	unsigned char* alpha;
} Image;

Image myImage
{
	10, 10, NULL, NULL
};

unsigned short pixels[] = {
	0x1111,
	0x2222,
	0xffff
};

void writeHeader( FILE* f, char* _symbolNameBase, SDL_Surface* image, bool _useFloats )
{
	fprintf( f, "#include \"Engine/Types.h\"\n" );
	fprintf( f, "#include \"Engine/Graphics/Image.h\"\n" );
	fprintf( f, "\n" );
}

void writePixels( FILE* f, char* _symbolNameBase, SDL_Surface* image, int* _pTotalOutputSize, bool _useFloats )
{
	fprintf( f, "const %s %s_pixels[] =\n{\n", _useFloats?"float":"uint16", _symbolNameBase );

	unsigned char* pixels = (unsigned char*)image->pixels;
	int x, y;
	for( y=0; y<image->h; y++ )
	{
		fprintf( f, "\t" );
		for( x=0; x<image->w; x++ )
		{
			int rofs = ((y*image->w)+x)*4;
			unsigned char b = pixels[ rofs+0 ];
			unsigned char g = pixels[ rofs+1 ];
			unsigned char r = pixels[ rofs+2 ];
			
			if( _useFloats )
			{
				float fr = r; fr /= 255.0f;
				float fg = g; fg /= 255.0f;
				float fb = b; fb /= 255.0f;
				fprintf( f, "%.2ff, %.2ff, %.2ff, ", fr, fg, fb );
			} else {
				//unsigned char a = pixels[ rofs+3 ];
				r >>= 3;
				g >>= 2;
				b >>= 3;
				unsigned short outcol = (r<<11) + (g<<5) + b;
				unsigned short nc = ((outcol&0x00ff)<<8) + ((outcol&0xff00)>>8);
				//printf("r=%i, g=%i, b=%i, a=%i\n", r, g, b, a);
				fprintf( f, "0x%04x,", nc );
			}
		}
		fprintf( f, "\n" );
	}
	
	*_pTotalOutputSize += image->w*image->h*2;
	
	fprintf( f, "};\n\n" );
}

void writeAlpha( FILE* f, char* _symbolNameBase, SDL_Surface* image, int* _pTotalOutputSize, bool _useFloats )
{
	fprintf( f, "const %s %s_alpha[] =\n{\n", _useFloats?"float":"uint8", _symbolNameBase );
	
	unsigned char* pixels = (unsigned char*)image->pixels;
	int x, y;
	for( y=0; y<image->h; y++ )
	{
		fprintf( f, "\t" );
		for( x=0; x<image->w; x++ )
		{
			int rofs = ((y*image->w)+x)*4;
			unsigned char a = pixels[ rofs+3 ];
			if( _useFloats )
			{
				float fa = a; fa /= 255.0f;
				fprintf( f, "%.2ff,", fa );
			} else
			{
				fprintf( f, "0x%02x,", a );
			}
		}
		fprintf( f, "\n" );
	}
	
	*_pTotalOutputSize += image->w*image->h;
	
	fprintf( f, "};\n\n" );
}

void writeImage( FILE* f, char* _symbolNameBase, SDL_Surface* _image, int* _pTotalOutputSize, bool _useFloats )
{
	fprintf( f, "extern \"C\" const Image %s;\n", _symbolNameBase );
	fprintf( f, "const Image %s =\n{\n", _symbolNameBase );
	fprintf( f, "\t%i,%i,\n", _image->w, _image->h );
	fprintf( f, "\t(%s*)&%s_pixels,\n", _useFloats?"float":"uint16", _symbolNameBase );
	if( SDL_ISPIXELFORMAT_ALPHA( _image->format->format ))
		fprintf( f, "\t(%s*)&%s_alpha,\n", _useFloats?"float":"uint8", _symbolNameBase );
	else
		fprintf( f, "\t(%s*)0,\n", _useFloats?"float":"uint8" );
	fprintf( f, "\t(uint8*)\"%s\",\n", _symbolNameBase );
	
	/*
	 
	 Don't output the blitting function anymore. Selecting the correct blit function will need to be done by the game code.
	 
	if( SDL_ISPIXELFORMAT_ALPHA( _image->format->format ))
		fprintf( f, "\t&imageBlitAlpha,\n");
	else
	{
		if((_image->w==96) && (_image->h==64))
		{
			fprintf( f, "\t&imageBlitFullScreen,\n" );
		}
		else
		{
			fprintf( f, "\t&imageBlitNoAlpha,\n" );
		}
	}
	 */
		
	fprintf( f, "};\n" );
}

void writeHeaderFile( FILE* f, char* _symbolNameBase, SDL_Surface* _image, bool _useFloats )
{
	fprintf( f, "#ifndef %s_data_h\n", _symbolNameBase );
	fprintf( f, "#define %s_data_h\n", _symbolNameBase );
	fprintf( f, "\n" );
	fprintf( f, "extern \"C\" const Image %s;\n", _symbolNameBase );
	fprintf( f, "\n" );
	fprintf( f, "#endif // %s_data_h\n", _symbolNameBase );
}

SDL_Surface* LoadImage( char* _fileName )
{
	SDL_Surface* image = IMG_Load( _fileName );
	//printf("Image=0x%016llx\n", (long long)image );
	bool isAlpha = SDL_ISPIXELFORMAT_ALPHA( image->format->format );
	bool isIndexed = SDL_ISPIXELFORMAT_INDEXED( image->format->format );

	//printf("w=%i, h=%i, bpp=%i, format=%i, isAlpha=%s, isIndexed=%s\n", image->w, image->h, image->format->BitsPerPixel, image->format->format, isAlpha?"Yes":"No", isIndexed?"Yes":"No" );
	
	return image;
}

FILE* openOutfileC( char* _baseOutFileName )
{
	char outname_c[ 2048 ];
	sprintf( outname_c, "%s.cpp", _baseOutFileName );
	FILE* f = fopen( outname_c, "w" );
	
	return f;
}

FILE* openOutfileH( char* _baseOutFileName )
{
	char outname_c[ 2048 ];
	sprintf( outname_c, "%s.h", _baseOutFileName );
	FILE* f = fopen( outname_c, "w" );
	
	return f;
}

int main( int _numargs, char** _apszArgh )
{
	if( _numargs < 4 )
	{
		printf("Usage error: Program need 3 arguments:\n");
		printf("  png2c <in_file.png> <out_file_base> <symbol_name> -floats\n");
		return -1;
	}

	char* pszInFileName = _apszArgh[ 1 ];
	char* pszOutFilenameBase = _apszArgh[ 2 ];
	char* pszSymbolNameBase = _apszArgh[ 3 ];
	
	// Assume that if a fifth argument is added it is "-floats", that is cool
	bool useFloats = _numargs == 5;
		
	
	//
	SDL_Surface* image = LoadImage( pszInFileName );

	//
	// Write cpp file
	//
	FILE* f = openOutfileC( pszOutFilenameBase );

	int totalOutputSize = 0;
	writeHeader( f, pszSymbolNameBase, image, useFloats );
	writePixels( f, pszSymbolNameBase, image, &totalOutputSize, useFloats );
	if( SDL_ISPIXELFORMAT_ALPHA( image->format->format ))
		writeAlpha( f, pszSymbolNameBase, image, &totalOutputSize, useFloats );
	writeImage( f, pszSymbolNameBase, image, &totalOutputSize, useFloats );
	
	fclose( f );
	
	
	//
	// Write h file
	//
	f = openOutfileH( pszOutFilenameBase );
	writeHeaderFile( f, pszSymbolNameBase, image, useFloats );
	fclose( f );

	printf("Total output size: %i\n", totalOutputSize );
	return 0;
}
