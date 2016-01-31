//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Arduino.h"

// TinyArcade game engine
#include "Engine/Graphics/Screen.h"
#include "Engine/Graphics/Image.h"
#include "Engine/types.h"
#include "Engine/Math/FixedPoint.h"
#include "Abstraction Layer/Joypad.h"
#include "Engine/Math/fpmath.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/TileRenderer.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/Audio/AudioMixer.h"
#include "Engine/Audio/AudioSource.h"

// Project specifics
#include "data/alldata.h"
#include "src/ContextManager.h"

//
extern AudioSource* bgm;

extern bool debugSpriteRenderer;

void(*pfnHBlankInterruptTitleScreen)(int);

void HBlankInterruptTitleScreen( int _scanline )
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

void titlescreen_setup()
{
	pfnHBlankInterruptTitleScreen = HBlankInterruptTitleScreen;
	
	// Reboot all cool systems
	gameObjectManager.Reboot();
	spriteRenderer.Reboot();
	audioMixer.Reboot();
}

void titlescreen_loop()
{
	uint32 startTime = micros();

	//
	// Update system stuff
	//
	padUpdate();
	
	//
	// Scanline rendered
	//
	unsigned short lineBuffer[ SCREEN_WIDTH ];
	uint16* screen = screenBuffer;

	spriteRenderer.FrameStart();

	int iScanline = 0;
	while( iScanline < SCREEN_HEIGHT )
	{
		int x;

		//
		if( pfnHBlankInterruptTitleScreen != NULL )
			pfnHBlankInterruptTitleScreen( iScanline );
		
		// Copy to screen
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			uint8 spriteCollisionMask;
			uint16 rgb = 0;
			bool renderedSprite = spriteRenderer.RenderPixel( x, &rgb, &spriteCollisionMask );

			lineBuffer[ x ] = rgb;
		}

		// Copy from line buffer to "hardware" screen
		for( x=0; x<SCREEN_WIDTH; x++ )
			*screen++ = lineBuffer[ x ];

		spriteRenderer.NextScanline( debugSpriteRenderer );
		
		iScanline++;
	}

	//
	// Reset debug triggers
	//
	debugSpriteRenderer = false;

	//
	//
	//
	audioMixer.Update();
	
	// Spin loop to wait. This is ... not ideal
	sint32 endTime = micros();
	sint32 dd = 16667 - (endTime-startTime);
	if( dd > 0 )
		delayMicroseconds( dd );
}

void titlescreen_exit()
{
	
}

void titlescreen_debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		contextGotoIngame();
	} else if( _trigger == 1 )
	{
		debugSpriteRenderer = true;
	}
}
