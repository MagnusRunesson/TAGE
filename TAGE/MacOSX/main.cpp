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
#include "Image.h"
#include "Joypad.h"
#include "Screen.h"
#include "types.h"
#include "bithelpers.h"

#include "timer.h"


//
//
//
extern void setup();
extern void loop();
extern void debugTrigger( int );

SDL_Window* window;
SDL_Surface* screenSurface;

const int SCREEN_PIXELSIZE = 2;

uint16* screenBuffer;

/*
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
 */

int gx;
int gy;
int gKeyDPadBuff;

extern uint8 gKeyBuff;


bool init()
{
	bool success = true;
	
	printf("init!\n");
	
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
	
	printf( "screen surface=0x%016llx\n", (unsigned long long)screenSurface );
	printf( "screen surface pixels=0x%016llx\n", (unsigned long long)(screenSurface->pixels) );
	printf( "screen surface width=%i, height=%i, bpp=%i, bytespp=%i\n", screenSurface->w, screenSurface->h, screenSurface->format->BitsPerPixel, screenSurface->format->BytesPerPixel );
	
	screenBuffer = new uint16[ SCREEN_WIDTH * SCREEN_HEIGHT ];
	printf("screen buffer=0x%016llx\n", (unsigned long long)screenBuffer );

	/*
	int s = SCREEN_WIDTH * SCREEN_HEIGHT;
	int i;
	for( i=0; i<s; i++ )
		screenBuffer[ i ] = i*10;
	 */
	
	gKeyBuff = 0;
	gKeyDPadBuff = 0;
	gx = 10;
	gy = 10;
	
	timerInit();
	
	return true;
}

void exit()
{
	delete[] screenBuffer;
	
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
	uint32* pixels = (uint32*)screenSurface->pixels;
	
	int scw = SCREEN_WIDTH*SCREEN_PIXELSIZE;
	//int sch = SCREEN_HEIGHT*SCREEN_PIXELSIZE;

	int x, y;
	int zx, zy;
	for( y=0; y<SCREEN_HEIGHT; y++ )
	{
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			int scrofs = (y*SCREEN_WIDTH)+x;

			uint16 srcColor = screenBuffer[ scrofs ];
			uint32 dstColor = Conv16to32( srcColor );
			
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
	//SDL_Delay( 15 );
}

const int SDL_KEYCODE_PRIMARY		= SDLK_z;
const int SDL_KEYCODE_SECONDARY		= SDLK_x;
const int SDL_KEYCODE_SELECT		= SDLK_SPACE;
const int SDL_KEYCODE_START			= SDLK_RETURN;

const int SDL_KEYCODE_DPAD_UP		= SDLK_UP;
const int SDL_KEYCODE_DPAD_DOWN		= SDLK_DOWN;
const int SDL_KEYCODE_DPAD_LEFT		= SDLK_LEFT;
const int SDL_KEYCODE_DPAD_RIGHT	= SDLK_RIGHT;

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
					
				case SDL_KEYCODE_PRIMARY:		SetBit( gKeyBuff, PAD_KEYMASK_PRIMARY );			break;
				case SDL_KEYCODE_SECONDARY:		SetBit( gKeyBuff, PAD_KEYMASK_SECONDARY );			break;
				case SDL_KEYCODE_SELECT:		SetBit( gKeyBuff, PAD_KEYMASK_SELECT );				break;
				case SDL_KEYCODE_START:			SetBit( gKeyBuff, PAD_KEYMASK_START );				break;
				case SDL_KEYCODE_DPAD_UP:		SetBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_UP );		break;
				case SDL_KEYCODE_DPAD_DOWN:		SetBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_DOWN );		break;
				case SDL_KEYCODE_DPAD_LEFT:		SetBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_LEFT );		break;
				case SDL_KEYCODE_DPAD_RIGHT:	SetBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_RIGHT );		break;
					
				case SDLK_0: debugTrigger( 0 ); break;
				case SDLK_1: debugTrigger( 0 ); break;
				case SDLK_2: debugTrigger( 0 ); break;
				case SDLK_3: debugTrigger( 0 ); break;
				case SDLK_4: debugTrigger( 0 ); break;
				case SDLK_5: debugTrigger( 0 ); break;
				case SDLK_6: debugTrigger( 0 ); break;
				case SDLK_7: debugTrigger( 0 ); break;
				case SDLK_8: debugTrigger( 0 ); break;
				case SDLK_9: debugTrigger( 0 ); break;
			}
		}
		else if( e.type == SDL_KEYUP )
		{
			switch( e.key.keysym.sym )
			{
				case SDL_KEYCODE_PRIMARY:		ClrBit( gKeyBuff, PAD_KEYMASK_PRIMARY );			break;
				case SDL_KEYCODE_SECONDARY:		ClrBit( gKeyBuff, PAD_KEYMASK_SECONDARY );			break;
				case SDL_KEYCODE_SELECT:		ClrBit( gKeyBuff, PAD_KEYMASK_SELECT );				break;
				case SDL_KEYCODE_START:			ClrBit( gKeyBuff, PAD_KEYMASK_START );				break;
				case SDL_KEYCODE_DPAD_UP:		ClrBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_UP );		break;
				case SDL_KEYCODE_DPAD_DOWN:		ClrBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_DOWN );		break;
				case SDL_KEYCODE_DPAD_LEFT:		ClrBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_LEFT );		break;
				case SDL_KEYCODE_DPAD_RIGHT:	ClrBit( gKeyDPadBuff, PAD_KEYMASK_DPAD_RIGHT );		break;
			}
		}
	}

	return quit;
}

bool update()
{
	bool quit = DoSDL();

	loop();
	
	blit_screenBufferToSDL();
	
	return !quit;
}

int main(int argc, const char * argv[])
{

	if( init() == true )
	{
		setup();	// Call Arduino like code
		
		// Main loop woot!
		while( update());
	}
	
	exit();
	
    return 0;
}
