//
//  ContextWinScreen.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "TinyScreen.h"
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
#include "Engine/Audio/AudioStream.h"

// Project specifics
#include "data/alldata.h"
#include "src/ContextManager.h"

//
#define WINSCREEN_CLOSETIMER_DURATION (60)
#define WINSCREEN_CLOSETIMER_SFXSTOP (WINSCREEN_CLOSETIMER_DURATION-5)

// Just reuse as many variables as possible from the title screen as to not use more RAM than necessary. Consider this old school overlays. :)
extern TinyScreen display;
extern uint16* lineBuffer;
extern void debugPrintSystems();
extern bool debugSpriteRenderer;
extern uint8 collisionBits[];
extern uint8 collisionIndices[];
extern AudioSource* sfxPressStart;
extern int titlescreenCloseTimer;

void(*pfnHBlankInterruptWinScreen)(int);

void HBlankInterruptWinScreen( int _scanline )
{
}

void winscreen_setup()
{
	pfnHBlankInterruptWinScreen = HBlankInterruptWinScreen;
	
	// Reboot all cool systems
	gameObjectManager.Reboot();
	spriteRenderer.Reboot();
	audioMixer.Reboot();

	
	// Sound effect for when the player decides to start the game
	sfxPressStart = audioMixer.GetChannel( 1 );
	sfxPressStart->SetData( &sfx_player_pickup );

	//audioMixer.SetFrequency( 32000 );
	AudioStream* pStream = audioMixer.GetStream( 0 );
	pStream->OpenStream( "bgm_title.raw" );
	pStream->Play();

	titlescreenCloseTimer = 0;
}

void winscreen_loop()
{
	uint32 startTime = micros();

	//
	// Update system stuff
	//
	padUpdate();
	
	//
	if( titlescreenCloseTimer == 0 )
	{
		// This is regular code, before the user press Start
		if( padGetPressed() & PAD_KEYMASK_PRIMARY )
		{
			audioMixer.GetStream( 0 )->Pause();
			titlescreenCloseTimer = WINSCREEN_CLOSETIMER_DURATION;
		}
	} else
	{
		titlescreenCloseTimer--;
		
		// Play the "confirm" audio. If it starts on the same frame as we stop the
		// bgm music the sound effect isn't heard, it just blends into the music.
		// So that's why there is a slight delay before playing the sound.
		if( titlescreenCloseTimer == WINSCREEN_CLOSETIMER_SFXSTOP )
			sfxPressStart->PlayFromBeginning();

		// Timer has run out. Start the game
		if( titlescreenCloseTimer == 0 )
			contextGotoTitleScreen();
	}
	
	//
	// Scanline rendered
	//
	spriteRenderer.FrameStart();

	display.setX( 0, SCREEN_WIDTH );
	display.setY( 0, SCREEN_HEIGHT );
	display.startData();

	int iScanline = 0;
	while( iScanline < SCREEN_HEIGHT )
	{
		int x;

		audioMixer.GetStream( 0 )->Update();
		
		//
		if( pfnHBlankInterruptWinScreen != NULL )
			pfnHBlankInterruptWinScreen( iScanline );
		
		// Copy to screen
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			uint16 rgb = (iScanline>>2);
			lineBuffer[ x ] = rgb;
		}
		
		spriteRenderer.RenderScanline( lineBuffer, collisionBits, collisionIndices );
			
#ifdef TAGE_TARGET_MACOSX
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			uint16 rgb = lineBuffer[ x ];
			uint16 newrgb2 = ((rgb&0x00ff)<<8) + ((rgb&0xff00)>>8);
			lineBuffer[ x ] = newrgb2;
		}
		display.writeBuffer( (uint8*)lineBuffer, SCREEN_WIDTH*2 );
#else
		display.writeBufferDMA((uint8*)lineBuffer, SCREEN_WIDTH*2 );
		while( !display.getReadyStatusDMA());
#endif
		
		spriteRenderer.NextScanline( debugSpriteRenderer );
		
		iScanline++;
	}
	
	display.endTransfer();

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

void winscreen_exit()
{
	
}

void winscreen_debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		contextGotoIngame();
	} else if( _trigger == 1 )
	{
		debugSpriteRenderer = true;
	} else if( _trigger == 9 )
	{
		debugPrintSystems();
	}
}
