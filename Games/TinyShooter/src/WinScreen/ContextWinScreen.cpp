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
#include "Engine/debug.h"

// Project specifics
#include "data/alldata.h"
#include "src/ContextManager.h"

//
#define WINSCREEN_CLOSETIMER_DURATION (100)
#define WINSCREEN_CLOSETIMER_SFXSTOP (WINSCREEN_CLOSETIMER_DURATION-5)
#define WINSCREEN_SKIPBUTTONINACTIVE (600)


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

Sprite* wsTextSprite[4];
Sprite* wsPlayerSprite;

#define NUM_STARS (64)

sint16 wsStarPositions[ NUM_STARS ];
uint16 wsStarColor;
int wsStarFade;
int wsPlayerShipX;
int wsPlayerShipWantedX;
int wsTextClipY;
int wsPlayerShipMoveX;
int wsSkipButtonTimer;

const sint16 wsStarStarts[ NUM_STARS ] =
{
	-15960,
	-17678,
	11482,
	-29653,
	14211,
	23241,
	3801,
	-30209,
	-20668,
	-31666,
	6297,
	-17322,
	-28019,
	23523,
	21684,
	-18616,
	-18152,
	-16110,
	17305,
	-13995,
	-20944,
	-21742,
	5678,
	2822,
	-19879,
	-6410,
	364,
	7639,
	-2167,
	7432,
	-7014,
	13459,
	-28855,
	-11980,
	28259,
	5186,
	-13068,
	-28914,
	-12252,
	-5402,
	30816,
	-19151,
	-23854,
	30409,
	30190,
	17762,
	-6131,
	-27316,
	-22269,
	-11210,
	58,
	-12158,
	-7035,
	-23111,
	-6891,
	-25693,
	-19555,
	-6475,
	28251,
	4712,
	11307,
	-19253,
	23270,
	-28087,
};

const sint16 wsStarSpeeds[ NUM_STARS ] = {
	-71,
	-145,
	-121,
	-74,
	-34,
	-104,
	-120,
	-158,
	-99,
	-109,
	-56,
	-117,
	-44,
	-130,
	-83,
	-103,
	-55,
	-49,
	-56,
	-116,
	-79,
	-49,
	-77,
	-37,
	-120,
	-149,
	-139,
	-118,
	-40,
	-39,
	-57,
	-50,
	-104,
	-83,
	-130,
	-97,
	-147,
	-45,
	-67,
	-133,
	-127,
	-80,
	-113,
	-104,
	-141,
	-129,
	-44,
	-107,
	-34,
	-85,
	-89,
	-33,
	-36,
	-88,
	-52,
	-66,
	-60,
	-84,
	-122,
	-135,
	-74,
	-106,
	-133,
	-104,
};

Sprite* getHBlankSprite( int _scanline )
{
	int i;
	for( i=0; i<4; i++ )
	{
		Sprite* spr = wsTextSprite[ i ];
		int top = spr->y;
		int bottom = top + spr->image->h;
		if((_scanline >= top) && (_scanline <= bottom))
			return spr;
	}
	
	return NULL;
}

void winscreenLoopTextClip()
{
	wsTextClipY++;
}

void HBlankInterruptWinScreen_Intro( int _scanline )
{
	Sprite* spr = getHBlankSprite( _scanline );
	if( spr )
	{
		int thisFrame = wsTextClipY >> 2;
		/*
		if( _scanline <= thisFrame )
			spr->x = 2;*/
		
		if( _scanline == thisFrame )
			spr->SetFlags( SPRITE_FLAG_DRAWWHITE );
		
		else if( _scanline > thisFrame+2 )
			spr->boundsLeft = 96;// ClrFlags( SPRITE_FLAG_DRAWWHITE );
	}
}

void HBlankInterruptWinScreen_Outro( int _scanline )
{
	Sprite* spr = getHBlankSprite( _scanline );
	if( spr )
	{
		int thisFrame = wsTextClipY >> 1;
		/*
		 if( _scanline <= thisFrame )
			spr->x = 2;*/
		
		if( _scanline < thisFrame )
			spr->boundsLeft = 96;
		else if( _scanline > thisFrame + 2 )
			spr->ClrFlags( SPRITE_FLAG_DRAWWHITE );
		else
		{
			spr->boundsLeft = 2;
			spr->SetFlags( SPRITE_FLAG_DRAWWHITE );
		}
	}
}

const Image* wsLineImage[ 4 ] =
{
	&sprite_winscreen_0,
	&sprite_winscreen_1,
	&sprite_winscreen_2,
	&sprite_winscreen_3,
};

void spawnLine( int _iLine )
{
	Sprite* spr = spriteRenderer.AllocateSprite( wsLineImage[ _iLine ]);
	spr->x = 2;
	if( _iLine == 3 )
		spr->y = 41;
	else
		spr->y = 12 + (_iLine*8);
	
	wsTextSprite[ _iLine ] = spr;
	
}

void winscreen_setup()
{
	pfnHBlankInterruptWinScreen = HBlankInterruptWinScreen_Intro;
	
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
	
	int i;
	for( i=0; i<4; i++ )
		spawnLine( i );
	
	int iStar;
	for( iStar=0; iStar<NUM_STARS; iStar++ )
		wsStarPositions[ iStar ] = wsStarStarts[ iStar ];
	
	wsPlayerSprite = spriteRenderer.AllocateSprite( &sprite_player );
	wsPlayerSprite->x = -20;
	wsPlayerSprite->y = 54;
	
	wsStarColor = 0;
	wsStarFade = 0;
	wsTextClipY = -350;
	
	wsPlayerShipX = -200;
	wsPlayerShipWantedX = 40;
	wsPlayerShipMoveX = 1;
	
	wsSkipButtonTimer = WINSCREEN_SKIPBUTTONINACTIVE;
}

void winscreenLoopFadeIn()
{
	if( wsStarFade > 192 )
		return;
	
	if( wsStarFade < 0 )
		return;
	
	if( titlescreenCloseTimer == 0 )
		wsStarFade++;
	else
	{
		wsStarFade-=2;
		if( wsStarFade < 0 )
			wsStarFade = 0;
	}
	
	int c = wsStarFade >> 3;
	if( c > 31 )
		c=31;
	
	uint16 rgb = (c<<11) + (c<<6) + c;
	uint16 newrgb = ((rgb&0x00ff)<<8) + ((rgb&0xff00)>>8);
	
	wsStarColor = newrgb;
}

void winscreenLoopMovePlayerShip()
{
	if( wsPlayerShipX < wsPlayerShipWantedX<<2 )
		wsPlayerShipX += wsPlayerShipMoveX;

	wsPlayerSprite->x = wsPlayerShipX >> 2;
}

void winscreen_loop()
{
	winscreenLoopFadeIn();
	winscreenLoopMovePlayerShip();
	winscreenLoopTextClip();
	
	int i;
	for( i=0; i<4; i++ )
	{
		Sprite* spr = wsTextSprite[ i ];
		spr->ClrFlags( SPRITE_FLAG_DRAWWHITE );
		spr->SetFlags( SPRITE_FLAG_ENABLED );
	}
	
	uint32 startTime = micros();

	//
	// Update system stuff
	//
	padUpdate();
	
	//
	if( titlescreenCloseTimer == 0 )
	{
		if( wsSkipButtonTimer > 0 )
		{
			wsSkipButtonTimer--;
		}
		else
		{
			// This is regular code, before the user press Start
			if( padGetPressed() & PAD_KEYMASK_PRIMARY )
			{
				audioMixer.GetStream( 0 )->Pause();
				titlescreenCloseTimer = WINSCREEN_CLOSETIMER_DURATION;
				wsPlayerShipWantedX = SCREEN_WIDTH;
				wsPlayerShipMoveX = 4;
				wsTextClipY = 12;
				wsStarFade = 191;
				pfnHBlankInterruptWinScreen = HBlankInterruptWinScreen_Outro;
			}
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
			uint16 rgb = 0;//(iScanline>>2);
			lineBuffer[ x ] = rgb;
		}

		// Advance the star
		int starX = wsStarPositions[ iScanline ];
		int wrx = starX >> 8;
		if((wrx >= 0) && (wrx<SCREEN_WIDTH))
			lineBuffer[ wrx ] = wsStarColor;
		starX += wsStarSpeeds[ iScanline ];
		if( starX < -32767 )
			starX += 65535;
		wsStarPositions[ iScanline ] = starX;
		
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
