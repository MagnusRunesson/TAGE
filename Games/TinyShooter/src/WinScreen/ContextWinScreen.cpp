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

/*
#define TITLESCREEN_CLOSETIMER_TOTALDURATION (60)
#define TITLESCREEN_CLOSETIMER_BLINKSHIFT (3)
#define TITLESCREEN_CLOSETIMER_SFXSTOP (TITLESCREEN_CLOSETIMER_TOTALDURATION-5)
#define TITLESCREEN_CREDITSTIMER_TOTAL (50)
#define TITLESCREEN_CREDITSTIMER_INVISBLE (30)
#define TITLESCREEN_CREDITSHEIGHT (45)

#define TITLESCREEN_FLASHTIMER_DURATION_REPEAT (240)
#define TITLESCREEN_FLASHTIMER_DURATION_INITIAL (60)
#define TITLESCREEN_FLASHTIMER_LETTER_DURATION (6)
#define TITLESCREEN_FLASHTIMER_START (56>>3)

const int titleSpriteFlashDelay[ 4+7 ] =
{
	43, 28, 21, 8,				// 8, 21, 28, 43,
	56, 48, 39, 29, 19, 9, 0,	// 0, 9, 19, 29, 39, 48, 56,
};
*/

extern TinyScreen display;
extern uint16* lineBuffer;


//
//extern AudioSource* bgm;
//AudioSource* sfxPressStart;

extern void debugPrintSystems();

extern bool debugSpriteRenderer;

/*
Sprite* titleSprites[ 4 + 7 ];	// TINY=4 letters, SHOOTER=7 letters
Sprite* titleScreenInsertCredits;
Sprite* titleScreenWinners;
int titlescreenCloseTimer;
int titleScreenTimer;
int titleScreenFlashTimer;
 */

extern uint8 collisionBits[];
extern uint8 collisionIndices[];

void(*pfnHBlankInterruptWinScreen)(int);

void HBlankInterruptWinScreen( int _scanline )
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

/*
void setupLetter( int _index, const Image* _pImage, int _x, int _y )
{
	Sprite* pSprite = spriteRenderer.AllocateSprite( _pImage );

	pSprite->x = _x;
	pSprite->y = _y;
	
	titleSprites[ _index ] = pSprite;
}
*/

void winscreen_setup()
{
	pfnHBlankInterruptWinScreen = HBlankInterruptWinScreen;
	
	// Reboot all cool systems
	gameObjectManager.Reboot();
	spriteRenderer.Reboot();
	audioMixer.Reboot();

	/*
	// Setup the letters
	int x, y;
	
	x = 23;
	y = 6;
	setupLetter( 0, &sprite_logo_tiny_t, x, y ); x += sprite_logo_tiny_t.w+1;
	setupLetter( 1, &sprite_logo_tiny_i, x, y ); x += sprite_logo_tiny_i.w+1;
	setupLetter( 2, &sprite_logo_tiny_n, x, y ); x += sprite_logo_tiny_n.w+1;
	setupLetter( 3, &sprite_logo_tiny_y, x, y ); x += sprite_logo_tiny_y.w+1;

	x = 15;
	y = 20;
	setupLetter(  4, &sprite_logo_shooter_s, x, y ); x += sprite_logo_shooter_s.w+1;
	setupLetter(  5, &sprite_logo_shooter_h, x, y ); x += sprite_logo_shooter_h.w+1;
	setupLetter(  6, &sprite_logo_shooter_o, x, y ); x += sprite_logo_shooter_o.w+1;
	setupLetter(  7, &sprite_logo_shooter_o, x, y ); x += sprite_logo_shooter_o.w+1;
	setupLetter(  8, &sprite_logo_shooter_t, x, y ); x += sprite_logo_shooter_t.w+1;
	setupLetter(  9, &sprite_logo_shooter_e, x, y ); x += sprite_logo_shooter_e.w+1;
	setupLetter( 10, &sprite_logo_shooter_r, x, y ); x += sprite_logo_shooter_r.w+1;
	
	titleScreenInsertCredits = spriteRenderer.AllocateSprite( &sprite_titlescreen_insertcredits );
	titleScreenInsertCredits->x = 21;
	titleScreenInsertCredits->y = TITLESCREEN_CREDITSHEIGHT;
	
	titleScreenWinners = spriteRenderer.AllocateSprite( &sprite_titlescreen_winnersdontusedrugs );
	titleScreenWinners->x = 7;
	titleScreenWinners->y = 58;
	
	// Cool background music
	//bgm = audioMixer.GetChannel( 0 );
	//bgm->SetData( &music_titlescreen );
	//bgm->PlayFromBeginning();
	
	// Sound effect for when the player decides to start the game
	sfxPressStart = audioMixer.GetChannel( 1 );
	sfxPressStart->SetData( &sfx_player_pickup );

	//audioMixer.SetFrequency( 32000 );
	AudioStream* pStream = audioMixer.GetStream( 0 );
	pStream->OpenStream( "bgm_title.raw" );
	pStream->Play();

	//
	titlescreenCloseTimer = 0;
	titleScreenFlashTimer = TITLESCREEN_FLASHTIMER_DURATION_INITIAL;
	 */
}

void winscreen_loop()
{
	uint32 startTime = micros();

	//
	// Update system stuff
	//
	padUpdate();
	
	/*
	//
	titleScreenFlashTimer--;
	if( titleScreenFlashTimer < TITLESCREEN_FLASHTIMER_START )
	{
		int i;
		for( i=0; i<4+7; i++ )
		{
			int offset = titleScreenFlashTimer - (titleSpriteFlashDelay[ i ] >> 3);
			if( offset >= 0 )
				titleSprites[ i ]->ClrFlags( SPRITE_FLAG_DRAWWHITE );
			else if( offset <= -TITLESCREEN_FLASHTIMER_LETTER_DURATION )
				titleSprites[ i ]->ClrFlags( SPRITE_FLAG_DRAWWHITE );
			else
				titleSprites[ i ]->SetFlags( SPRITE_FLAG_DRAWWHITE );
		}
		
		if( titleScreenFlashTimer == -TITLESCREEN_FLASHTIMER_START )
			titleScreenFlashTimer = TITLESCREEN_FLASHTIMER_DURATION_REPEAT;
	}

	//
	if( titlescreenCloseTimer == 0 )
	{
		titleScreenTimer--;
		if( titleScreenTimer <= 0 )
			titleScreenTimer += TITLESCREEN_CREDITSTIMER_TOTAL;
		
		if( titleScreenTimer > TITLESCREEN_CREDITSTIMER_INVISBLE )
			titleScreenInsertCredits->y = -10;
		else
			titleScreenInsertCredits->y = TITLESCREEN_CREDITSHEIGHT;
		
		// This is regular code, before the user press Start
		if( padGetPressed() & PAD_KEYMASK_PRIMARY )
		{
			audioMixer.GetStream( 0 )->Pause();
			//audioMixer.SetFrequency( 11025 );
			titlescreenCloseTimer = TITLESCREEN_CLOSETIMER_TOTALDURATION;
			if( titleScreenFlashTimer > TITLESCREEN_FLASHTIMER_START )
				titleScreenFlashTimer = TITLESCREEN_FLASHTIMER_START;
		}
	}
	else
	{
		// User have pressed start and we're just waiting
		titlescreenCloseTimer--;

		// Flashing text
		if((titlescreenCloseTimer>>TITLESCREEN_CLOSETIMER_BLINKSHIFT) & 1 )
			titleScreenInsertCredits->y = -10;
		else
			titleScreenInsertCredits->y = TITLESCREEN_CREDITSHEIGHT;
		
		// Play the "confirm" audio. If it starts on the same frame as we stop the
		// bgm music the sound effect isn't heard, it just blends into the music.
		// So that's why there is a slight delay before playing the sound.
		if( titlescreenCloseTimer == TITLESCREEN_CLOSETIMER_SFXSTOP )
			sfxPressStart->PlayFromBeginning();

		// Timer has run out. Start the game
		if( titlescreenCloseTimer == 0 )
			contextGotoIngame();
	}
	*/
	
	//
	// Scanline rendered
	//
	//uint16* screen = screenBuffer;

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
		
		//	spriteRenderer.RenderPixel( x, &rgb, &spriteCollisionMask );
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
		
		/*
		// Copy from line buffer to "hardware" screen
		for( x=0; x<SCREEN_WIDTH; x++ )
			*screen++ = lineBuffer[ x ];*/

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
