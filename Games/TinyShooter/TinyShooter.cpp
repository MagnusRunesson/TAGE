//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Arduino.h"

// TinyArcade game engine
#include "Screen.h"
#include "types.h"
#include "FixedPoint.h"
#include "Joypad.h"
#include "fpmath.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "TileRenderer.h"

// Project specifics
#include "alldata.h"

//
Camera mainCamera;
TileRenderer* background;
FixedPoint cameraScroll;
FixedPoint cameraScrollSpeed;

bool debugSpriteRenderer;

int worldWidth;

#define MAX( a, b ) ((a>b)?a:b)
#define MIN( a, b ) ((a<b)?a:b)

void(*pfnHBlankInterrupt)(int);

void HBlankInterrupt( int _scanline )
{
	/*
	if( _scanline < 5 )
	{
		int x, y;
		background->GetPosition( &x, &y );
		x--;
		background->SetPosition( x, y );
	} else if( _scanline > 59 )
	{
		int x, y;
		background->GetPosition( &x, &y );
		x++;
		background->SetPosition( x, y );
	}
	 */
	
	//printf( "Scanline=%i\n", _scanline );
}

void setup()
{
	debugSpriteRenderer = false;

	worldWidth = tilemap_spacebase.Width * tilebank_spacebase.TileWidth;
	background = new TileRenderer( &tilemap_spacebase, &tilebank_spacebase );
	
	//
	// Scrolling a 10 screen wide level (10 screens in total, scrolling 9 screens at 864 pixels) at FixedPoint( 0, 5 ) takes about 5 minutes
	// Scrolling 1 screen (96 pixels) at FixedPoint( 0, 5 ) takes 35 seconds
	//
	// Set up game camera
	Camera::main = &mainCamera;
	cameraScroll = 0;
	cameraScrollSpeed = FixedPoint( 0, 5 );

	pfnHBlankInterrupt = HBlankInterrupt;
}

void loop()
{
	uint32 startTime = micros();

	//
	// Update system stuff
	//
	padUpdate();
	
	//
	// Update all game objects
	//
	gameObjectManager.Update();

	if( cameraScroll < worldWidth - 96 )
	{
		cameraScroll += cameraScrollSpeed;
		if( cameraScroll > worldWidth - 96 )
		{
			cameraScroll = worldWidth-96;
		}
	}

	//
	//
	//
	int camx = cameraScroll.GetInteger();
	mainCamera.SetWorldPosition( camx, 0 );
	background->SetPosition( camx, 0 );
	
	//
	// Tell all game objects that it is time to be rendered
	//
	gameObjectManager.Render();
	
	
	//
	// Scanline rendered
	//
	unsigned short lineBuffer[ SCREEN_WIDTH ];
	uint16* screen = screenBuffer;
	uint16* mirrorScreen = screen;

	spriteRenderer.FrameStart();
	background->FrameStart();


	// Set this to the number of pixel rows in screen space that should be mirrored to enable the mirror effect
	int mirrorHeight = 0;
	
	/*
	 
	 Or use this code to use world space Y coordinate to enable the water effect
	 
	int worldMirrorStart = 230;		// Presto
	int mirrorHeight = (camy+SCREEN_HEIGHT) - worldMirrorStart;
	if( mirrorHeight < 0 )
		mirrorHeight = 0;
	 */
	
	int mirrorStart = SCREEN_HEIGHT-mirrorHeight;
	int copyStart = mirrorStart-mirrorHeight;
	
	int iScanline = 0;
	while( iScanline < mirrorStart )
	{
		// Clear line buffer
		int x;
		for( x=0; x<SCREEN_WIDTH; x++ )
			lineBuffer[ x ] = 0;

		if( pfnHBlankInterrupt != NULL )
			pfnHBlankInterrupt( iScanline );
		
		// Render sprites to line buffer
		background->RenderScanline( lineBuffer );
		spriteRenderer.RenderScanline( lineBuffer );

		// Copy to screen
		for( x=0; x<SCREEN_WIDTH; x++ )
			*screen++ = lineBuffer[ x ];

		// Mirror test
		if( iScanline >= copyStart )
		{
			int destY = SCREEN_HEIGHT - (iScanline - copyStart);
			for( x=0; x<SCREEN_WIDTH; x++ )
			{
				uint16 rgb = lineBuffer[ x ];
				int r = (rgb >> 11);
				int g = (rgb >> 6) & 0x001f;
				int b = rgb & 0x001f;
				
				int i = (r+g+b)/3;
				int hi = i>>1;
				
				rgb = ((hi << 11) + (hi << 6) + i);
				mirrorScreen[ ((destY-1)*SCREEN_WIDTH) + x ] = rgb;
			}
		}

		spriteRenderer.NextScanline( debugSpriteRenderer );
		background->NextScanline();
		
		iScanline++;
	}

	//
	// Reset debug triggers
	//
	debugSpriteRenderer = false;

	// Spin loop to wait. This is ... not ideal
	uint32 endTime = micros();
	uint32 dd = 16667 - (endTime-startTime);
	delayMicroseconds( dd );
}

void debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		debugSpriteRenderer = true;
	}
}
