//
//  main.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-11-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "FixedPoint.h"

SDL_Window* window;
SDL_Surface* screenSurface;

const int SCREEN_WIDTH = 96;
const int SCREEN_HEIGHT = 64;

const int SCREEN_PIXELSIZE = 10;

Uint16* screenBuffer;
Uint16* background;

const int COLORSHIFT_16_R = 11;
const int COLORSHIFT_16_G = 5;
const int COLORSHIFT_16_B = 0;
const int COLORWIDTH_16_R = 0x1f;
const int COLORWIDTH_16_G = 0x3f;
const int COLORWIDTH_16_B = 0x1f;

const Uint16 COLORMASK_16_R = COLORWIDTH_16_R << COLORSHIFT_16_R;
const Uint16 COLORMASK_16_G = COLORWIDTH_16_R << COLORSHIFT_16_G;
const Uint16 COLORMASK_16_B = COLORWIDTH_16_R << COLORSHIFT_16_B;

const Uint16 shiftMask[] =
{
	0xFFFF,	// Shift 0 bits
	0xF7DE, // Shift 1 bit
	0xE79C, // Shift 2 bits
	0xC718, // Shift 3 bits
	0x8610, // Shift 4 bits
};

FixedPoint fpX;
FixedPoint fpY;
FixedPoint fpSpeed;

int gx;
int gy;
int gKeyBuff;
int gKeyDPadBuff;

bool init()
{
	bool success = true;
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf("Failed to init SDL. Error: %s\n", SDL_GetError());
		success = false;
	} else
	{
		window = SDL_CreateWindow("TinyArcade", 10, 10, SCREEN_WIDTH*SCREEN_PIXELSIZE, SCREEN_HEIGHT*SCREEN_PIXELSIZE, SDL_WINDOW_INPUT_FOCUS );
		if( window == NULL )
		{
			printf("Failed to create window. Error: %s\n", SDL_GetError());
			success = false;
		} else
		{
			printf("Happy fun times!\n");
			screenSurface = SDL_GetWindowSurface( window );
		}
	}
	
	screenBuffer = new Uint16[ SCREEN_WIDTH * SCREEN_HEIGHT ];
	
	/*
	int s = SCREEN_WIDTH * SCREEN_HEIGHT;
	int i;
	for( i=0; i<s; i++ )
		screenBuffer[ i ] = i*10;
	 */
	
	background = new Uint16[ SCREEN_WIDTH * SCREEN_HEIGHT ];
	int x, y;
	for( y=0; y<SCREEN_HEIGHT; y++ )
	{
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			int r = (y/2) & COLORWIDTH_16_R;
			int g = (63-(y/2)) & COLORWIDTH_16_G;
			int b = (x/3) & COLORWIDTH_16_B;
			Uint16 c = (r<<COLORSHIFT_16_R) + (g<<COLORSHIFT_16_G) + (b<<COLORSHIFT_16_B);
			background[ (y*SCREEN_WIDTH) + x ] = c;
		}
	}

	gKeyBuff = 0;
	gKeyDPadBuff = 0;
	gx = 10;
	gy = 10;
	
	fpSpeed = FixedPoint( 0, 50 );
	fpX = 10;
	fpY = 10;
	
	return true;
}

void exit()
{
	delete[] screenBuffer;
	delete[] background;
	
	SDL_Quit();
}

Uint32 Doo( Uint16 _src, int _shiftDown, int _width, int _shiftUp )
{
	Uint32 ret = _src >> _shiftDown;
	ret &= _width;
	ret <<= _shiftUp;
	return ret;
}

Uint32 Conv16to32( Uint16 src )
{
	Uint32 ret = 0;
	
	Uint32 r = Doo( src, COLORSHIFT_16_R, COLORWIDTH_16_R, 16+3 );
	Uint32 g = Doo( src, COLORSHIFT_16_G, COLORWIDTH_16_G, 8+2 );
	Uint32 b = Doo( src, COLORSHIFT_16_B, COLORWIDTH_16_B, 0+3 );

	ret = r | g | b;
	
	return ret;
}

void blit_screenBufferToSDL()
{
	Uint32* pixels = (Uint32*)screenSurface->pixels;
	
	int scw = SCREEN_WIDTH*SCREEN_PIXELSIZE;
	//int sch = SCREEN_HEIGHT*SCREEN_PIXELSIZE;

	/*
	int x, y;
	for( y=0; y<sch; y++ )
	{
		for( x=0; x<scw; x++ )
		{
			// -RGB
			//pixels[ (y*scw)+x ] = 0x4070a0e0;
		}
	}
	 */

	int x, y;
	int zx, zy;
	for( y=0; y<SCREEN_HEIGHT; y++ )
	{
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			int scrofs = (y*SCREEN_WIDTH)+x;

			Uint16 srcColor = screenBuffer[ scrofs ];
			Uint32 dstColor = Conv16to32( srcColor );
			
			for( zy=0; zy<SCREEN_PIXELSIZE; zy++ )
			{
				for( zx=0; zx<SCREEN_PIXELSIZE; zx++ )
				{
					int wrx = (x*SCREEN_PIXELSIZE) + zx;
					int wry = (y*SCREEN_PIXELSIZE) + zy;
					int wrofs = (wry*scw) + wrx;
					
					pixels[ wrofs ] = dstColor;
				}
			}
		}
	}

	SDL_UpdateWindowSurface( window );
	SDL_Delay( 15 );
}

int SDL_KEYMASK_PRIMARY		= (1<<0);
int SDL_KEYMASK_SECONDARY	= (1<<1);
int SDL_KEYMASK_SELECT		= (1<<2);
int SDL_KEYMASK_START		= (1<<3);
int SDL_KEYMASK_DPAD_UP		= (1<<16);
int SDL_KEYMASK_DPAD_DOWN	= (1<<17);
int SDL_KEYMASK_DPAD_LEFT	= (1<<18);
int SDL_KEYMASK_DPAD_RIGHT	= (1<<19);

const int SDL_KEYCODE_PRIMARY = SDLK_z;
const int SDL_KEYCODE_SECONDARY = SDLK_x;
const int SDL_KEYCODE_SELECT = SDLK_SPACE;
const int SDL_KEYCODE_START = SDLK_RETURN;

const int SDL_KEYCODE_DPAD_UP = SDLK_UP;
const int SDL_KEYCODE_DPAD_DOWN = SDLK_DOWN;
const int SDL_KEYCODE_DPAD_LEFT = SDLK_LEFT;
const int SDL_KEYCODE_DPAD_RIGHT = SDLK_RIGHT;


inline void SetBit( int* _value, int _bitMask )
{
	*_value |= _bitMask;
}

inline void ClrBit( int* _value, int _bitmask )
{
	*_value &= ~_bitmask;
}

inline bool HasBit( int _value, int _bitmask )
{
	return (_value&_bitmask) == _bitmask;
}

bool DoSDL()
{
	bool quit = false;
	SDL_Event e;
	
	while( SDL_PollEvent( &e ))
	{
		if( e.type == SDL_QUIT )
		{
			quit = true;
		}
		else if( e.type == SDL_KEYDOWN )
		{
			switch( e.key.keysym.sym )
			{
				case SDLK_ESCAPE:
					quit = true;
					break;
					
				case SDL_KEYCODE_PRIMARY:		SetBit( &gKeyBuff, SDL_KEYMASK_PRIMARY );			break;
				case SDL_KEYCODE_SECONDARY:		SetBit( &gKeyBuff, SDL_KEYMASK_SECONDARY );			break;
				case SDL_KEYCODE_SELECT:		SetBit( &gKeyBuff, SDL_KEYMASK_SELECT );			break;
				case SDL_KEYCODE_START:			SetBit( &gKeyBuff, SDL_KEYMASK_START );				break;
				case SDL_KEYCODE_DPAD_UP:		SetBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_UP );		break;
				case SDL_KEYCODE_DPAD_DOWN:		SetBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_DOWN );		break;
				case SDL_KEYCODE_DPAD_LEFT:		SetBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_LEFT );		break;
				case SDL_KEYCODE_DPAD_RIGHT:	SetBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_RIGHT );	break;
			}
		}
		else if( e.type == SDL_KEYUP )
		{
			switch( e.key.keysym.sym )
			{
				case SDL_KEYCODE_PRIMARY:		ClrBit( &gKeyBuff, SDL_KEYMASK_PRIMARY );			break;
				case SDL_KEYCODE_SECONDARY:		ClrBit( &gKeyBuff, SDL_KEYMASK_SECONDARY );			break;
				case SDL_KEYCODE_SELECT:		ClrBit( &gKeyBuff, SDL_KEYMASK_SELECT );			break;
				case SDL_KEYCODE_START:			ClrBit( &gKeyBuff, SDL_KEYMASK_START );				break;
				case SDL_KEYCODE_DPAD_UP:		ClrBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_UP );		break;
				case SDL_KEYCODE_DPAD_DOWN:		ClrBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_DOWN );		break;
				case SDL_KEYCODE_DPAD_LEFT:		ClrBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_LEFT );		break;
				case SDL_KEYCODE_DPAD_RIGHT:	ClrBit( &gKeyDPadBuff, SDL_KEYMASK_DPAD_RIGHT );	break;
			}
		}
	}

	return quit;
}

Uint8 gkeys;
Uint8 getPad( Sint8* _x, Sint8* _y )
{
	gkeys <<= 4;
	gkeys |= gKeyBuff;
	
	*_x = 0;
	*_y = 0;
	if( HasBit( gKeyDPadBuff, SDL_KEYMASK_DPAD_UP ))	*_y -= 1;
	if( HasBit( gKeyDPadBuff, SDL_KEYMASK_DPAD_DOWN ))	*_y += 1;
	if( HasBit( gKeyDPadBuff, SDL_KEYMASK_DPAD_LEFT ))	*_x -= 1;
	if( HasBit( gKeyDPadBuff, SDL_KEYMASK_DPAD_RIGHT ))	*_x += 1;
	
	return gkeys;
}

bool update()
{
	bool quit = DoSDL();

	int w = 5;
	int h = 5;
	int mx = SCREEN_WIDTH - w;
	int my = SCREEN_HEIGHT - h;
	Sint8 padX, padY;
	Uint16 keys = getPad( &padX, &padY );

	FixedPoint spx = padX;
	spx *= fpSpeed;
	FixedPoint spy = padY;
	spy *= fpSpeed;
	
	fpX += spx;
	fpY += spy;

	if( fpX < 0 )	fpX = 0;
	if( fpX > mx )	fpX = mx;
	if( fpY < 0 )	fpY = 0;
	if( fpY > my )	fpY = my;
	
	
	memcpy( screenBuffer, background, SCREEN_HEIGHT * SCREEN_WIDTH * 2 );
	int dx, dy;
	int x = fpX.GetInteger();
	int y = fpY.GetInteger();
	for( dy=0; dy<h; dy++ )
	{
		for( dx=0; dx<w; dx++ )
		{
			int scrofs = ((y+dy)*SCREEN_WIDTH)+x+dx;
			
			Uint16 srcCol = screenBuffer[ scrofs ];
			srcCol &= shiftMask[ dx ];
			srcCol >>= dx;
			screenBuffer[ scrofs ] = srcCol;
		}
	}
	
	blit_screenBufferToSDL();
	
	return !quit;
}

int main(int argc, const char * argv[])
{

	if( init() == true )
	{
		// Main loop woot!
		while( update());
	}
	
	exit();
	
    return 0;
}
