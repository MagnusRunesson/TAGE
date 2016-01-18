//
//  main.cpp
//  png2tilefest
//
//  Created by Magnus Runesson on 01/12/15.
//  Copyright (c) 2015 Pokewhat. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>

void writeHeader( FILE* f, char* _symbolNameBase, SDL_Surface* image )
{
	fprintf( f, "#include \"Tilebank.h\"\n\n" );
}

void writePixel( FILE* f, unsigned char* source )
{
	unsigned char b = source[ 0 ];
	unsigned char g = source[ 1 ];
	unsigned char r = source[ 2 ];
	//unsigned char a = pixels[ rofs+3 ];
	r >>= 3;
	g >>= 2;
	b >>= 3;
	unsigned short outcol = (r<<11) + (g<<5) + b;
	//printf("r=%i, g=%i, b=%i, a=%i\n", r, g, b, a);
	fprintf( f, "0x%04x,", outcol );
}

int writePixels( FILE* f, char* _symbolNameBase, SDL_Surface* image, int tileWidth, int tileHeight )
{
	fprintf( f, "uint16 %s_pixels[] =\n{\n", _symbolNameBase );
	
	unsigned char* pixels = (unsigned char*)image->pixels;
	int itile=0;
	int x, y;
	for( y=0; y<image->h; y+=tileHeight )
	{
		for( x=0; x<image->w; x+=tileWidth )
		{
			fprintf( f, "\t// Tile %i\n", itile );
			itile++;
			
			int tx, ty;
			for( ty=0; ty<tileHeight; ty++ )
			{
				fprintf( f, "\t" );
				for( tx=0; tx<tileWidth; tx++ )
				{
					int rofs = (((y+ty)*image->w)+(x+tx))*4;
					writePixel( f, &pixels[ rofs ]);
				}
				fprintf( f, "\n" );
			}
			fprintf( f, "\n" );
		}
	}
	
	fprintf( f, "};\n\n" );
	
	return itile;
}

void writeAlpha( FILE* f, char* _symbolNameBase, SDL_Surface* image, int tileWidth, int tileHeight )
{
	fprintf( f, "uint8 %s_alpha[] =\n{\n", _symbolNameBase );
	
	unsigned char* pixels = (unsigned char*)image->pixels;
	int itile=0;
	int x, y;
	for( y=0; y<image->h; y+=tileHeight )
	{
		for( x=0; x<image->w; x+=tileWidth )
		{
			fprintf( f, "\t// Tile %i\n", itile );
			itile++;
			
			int tx, ty;
			for( ty=0; ty<tileHeight; ty++ )
			{
				fprintf( f, "\t" );
				for( tx=0; tx<tileWidth; tx++ )
				{
					int rofs = (((y+ty)*image->w)+(x+tx))*4;
					unsigned char a = pixels[ rofs+3 ];
					fprintf( f, "0x%02x,", a );
				}
				fprintf( f, "\n" );
			}
			fprintf( f, "\n" );
		}
	}
	
	fprintf( f, "};\n\n" );
}

void writeTileBank( FILE* f, char* _symbolNameBase, SDL_Surface* _image, int tileWidth, int tileHeight, int numTiles )
{
	fprintf( f, "CTileBank %s =\n{\n", _symbolNameBase );
	fprintf( f, "\t%i,%i,\n", tileWidth, tileHeight );
	fprintf( f, "\t%i,\n", numTiles );
	fprintf( f, "\t(uint16*)&%s_pixels,\n", _symbolNameBase );
	if( SDL_ISPIXELFORMAT_ALPHA( _image->format->format ))
		fprintf( f, "\t(uint8*)&%s_alpha,\n", _symbolNameBase );
	else
		fprintf( f, "\t(uint8*)0,\n" );
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

void writeHeaderFile( FILE* f, char* _symbolNameBase, SDL_Surface* _image )
{
	fprintf( f, "#ifndef %s_tilebank_h\n", _symbolNameBase );
	fprintf( f, "#define %s_tilebank_h\n", _symbolNameBase );
	fprintf( f, "\n" );
	fprintf( f, "#include \"Tilebank.h\"\n" );
	fprintf( f, "\n" );
	fprintf( f, "extern CTileBank %s;\n", _symbolNameBase );
	fprintf( f, "\n" );
	fprintf( f, "#endif // %s_tilebank_h\n", _symbolNameBase );
}

SDL_Surface* LoadImage( char* _fileName )
{
	SDL_Surface* image = IMG_Load( _fileName );
	printf("Image=0x%016llx\n", (long long)image );
	bool isAlpha = SDL_ISPIXELFORMAT_ALPHA( image->format->format );
	bool isIndexed = SDL_ISPIXELFORMAT_INDEXED( image->format->format );
	
	printf("w=%i, h=%i, bpp=%i, format=%i, isAlpha=%s, isIndexed=%s\n", image->w, image->h, image->format->BitsPerPixel, image->format->format, isAlpha?"Yes":"No", isIndexed?"Yes":"No" );
	
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
	if( _numargs != 6 )
	{
		printf("Usage error: Program need 5 arguments:\n");
		printf("  png2tilefest <in_file.png> <out_file_base> <symbol_name> <tile_width> <tile_height>\n");
		return -1;
	}
	
	char* pszInFileName = _apszArgh[ 1 ];
	char* pszOutFilenameBase = _apszArgh[ 2 ];
	char* pszSymbolNameBase = _apszArgh[ 3 ];
	int tileWidth = atoi( _apszArgh[ 4 ]);
	int tileHeight = atoi( _apszArgh[ 5 ]);

	printf("tile width=%i, height=%i\n", tileWidth, tileHeight );

	//
	SDL_Surface* image = LoadImage( pszInFileName );
	
	//
	// Write cpp file
	//
	FILE* f = openOutfileC( pszOutFilenameBase );
	
	writeHeader( f, pszSymbolNameBase, image );
	int numTiles = writePixels( f, pszSymbolNameBase, image, tileWidth, tileHeight );
	if( SDL_ISPIXELFORMAT_ALPHA( image->format->format ))
		writeAlpha( f, pszSymbolNameBase, image, tileWidth, tileHeight );
	writeTileBank( f, pszSymbolNameBase, image, tileWidth, tileHeight, numTiles );
	
	fclose( f );
	
	
	//
	// Write h file
	//
	f = openOutfileH( pszOutFilenameBase );
	writeHeaderFile( f, pszSymbolNameBase, image );
	fclose( f );

	return 0;
}
