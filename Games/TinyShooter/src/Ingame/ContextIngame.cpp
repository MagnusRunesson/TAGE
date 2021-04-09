//#define PERF_FEST

//
//  ContextIngame.cpp
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
#include "Engine/Types.h"
#include "Engine/Math/FixedPoint.h"
#include "Engine/Math/fpmath.h"
#include "Engine/Scene/Camera.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/TileRenderer.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/Audio/AudioMixer.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Debug.h"
#include "Abstraction layer/Joypad.h"
#include "Abstraction layer/Timer.h"

// Project specifics
#include "data/alldata.h"
#include "src/Ingame/Enemy.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/Path.h"
#include "src/Ingame/PathFollower.h"
#include "src/Ingame/ExplosionManager.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/Player.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/HUD.h"
#include "src/Ingame/PickupManager.h"
#include "src/Ingame/EnemyBulletManager.h"
#include "src/ContextManager.h"
#include "src/Ingame/spacebase_levelscrollfunc.h"

//
int expectedFrameTime = 16667;
Camera mainCamera;
TileRenderer* background;
TileRenderer* playfield;
int mapScroll;
FixedPoint cameraScroll;
FixedPoint cameraScrollSpeed;
//AudioSource* bgm;
uint32 lineBufferA32[ SCREEN_WIDTH/2 ];
uint32 lineBufferB32[ SCREEN_WIDTH/2 ];
uint32 lineBufferTemplate32[ SCREEN_WIDTH/2 ];
uint16* lineBuffer = (uint16*)lineBufferA32;
uint16* lineBufferTemplate = (uint16*)lineBufferTemplate32;

uint8 collisionBits[ SCREEN_WIDTH ];
uint8 collisionIndices[ SCREEN_WIDTH*8 ];

bool debugSpriteRenderer;
bool doCameraScroll;
bool gameOver;
int gameOverTimer;

void ingameGameOverInit();
void ingameGameOverStart();
void ingameGameOverUpdate();

extern TinyScreen display;

int worldWidth;

#define MAX( a, b ) ((a>b)?a:b)
#define MIN( a, b ) ((a<b)?a:b)

void(*pfnHBlankInterrupt)(int);
void(*pfnIngameCallback)();

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

inline uint16 byteswap( uint16 _c )
{
	return ((_c&0x00ff)<<8) + ((_c&0xff00)>>8);
}

inline uint16 rgb16( uint8 _r, uint8 _g, uint8 _b )
{
	uint16 rgb = ((_r<<11) + (_g<<5) + _b);
	return byteswap( rgb );
}

void GenerateTemplateGrey( int _darkGreyStart, int _brightGreyStart, int _darkGreyStart2, int _blackStart )
{
	uint16 darkGrey = rgb16( 4, 8, 5 );
	uint16 brightGrey = rgb16( 8, 16, 10 );

	if( _darkGreyStart > SCREEN_WIDTH ) _darkGreyStart=SCREEN_WIDTH;
	if( _brightGreyStart > SCREEN_WIDTH ) _brightGreyStart=SCREEN_WIDTH;
	if( _darkGreyStart2 > SCREEN_WIDTH ) _darkGreyStart2=SCREEN_WIDTH;
	if( _blackStart > SCREEN_WIDTH ) _blackStart=SCREEN_WIDTH;

	int x=0;
	while( x<_darkGreyStart )
	{
		lineBufferTemplate[ x ] = 0x0000;
		x++;
	}
	
	while( x<_brightGreyStart )
	{
		lineBufferTemplate[ x ] = darkGrey;
		x++;
	}
	
	while( x<_darkGreyStart2 )
	{
		lineBufferTemplate[ x ] = brightGrey;
		x++;
	}

	while( x<_blackStart )
	{
		lineBufferTemplate[ x ] = darkGrey;
		x++;
	}
	
	while( x < SCREEN_WIDTH )
	{
		lineBufferTemplate[ x ] = 0x0000;
		x++;
	}
}

int currentFunc;
const LevelScrollFunc* levelScrollFuncs = spacebase_levelscrollfuncs;
const int numFuncs = spacebase_levelscrollfuncs_numfuncs;

#ifdef PERF_FEST

float avgTime;
float avgTime2;
const float avgTimeSamples = 60.0f;

#endif

float addToAverage( float _currentAverage, float _newTime, float _numSamples )
{
	float allTime = _currentAverage * _numSamples;
	allTime -= _currentAverage;
	allTime += _newTime;
	_currentAverage = allTime / _numSamples;
	return _currentAverage;
}

void ingame_setup()
{
	// Reboot all cool systems
	gameObjectManager.Reboot();
	spriteRenderer.Reboot();
	audioMixer.Reboot();

	// Level specific, which column func to all
	currentFunc = 0;

	//
	debugSpriteRenderer = false;
	pfnHBlankInterrupt = HBlankInterrupt;
	pfnIngameCallback = NULL;
	gameOver = false;

	//
	worldWidth = (tilemap_spacebase.Width-2) * tilebank_spacebase.TileWidth;
	playfield = new TileRenderer( &tilemap_spacebase, &tilebank_spacebase );
	background = new TileRenderer( &tilemap_spacebase_background, &tilebank_spacebase );
	//bgm = audioMixer.GetChannel( 2 );
	
	//
	// Scrolling a 10 screen wide level (10 screens in total, scrolling 9 screens at 864 pixels) at FixedPoint( 0, 5 ) takes about 300 seconds (5 minutes)
	// Scrolling 1 screen (96 pixels) at FixedPoint( 0, 5 ) takes 35 seconds
	// Scrolling 1 pixel at FixedPoint( 0, 5 ) takes ~2.8 seconds
	//
	// 300/864=0.347
	// 120/864=0.139
	// 0.347/0.139=2.496
	// 2.496*0.05=0.12
	// So scrolling at FixedPoint( 0, 12 ) should make the level whosh by at 2 minutes
	//
	// Set up game camera
	Camera::main = &mainCamera;
	cameraScroll = 0;
	mapScroll = 0;
	
	// Fast forward in the map
	int i;
	for( i=0; i<numFuncs; i++ )
	{
		if( levelScrollFuncs[ i ].x < mapScroll )
			currentFunc++;
		else
			break;
	}
	
	cameraScrollSpeed = FixedPoint( 0, 12 );
	doCameraScroll = true;

	hudInit();
	playerInit( mapScroll );
	pickupInit();
	playerBulletsInit();
	explosionsInit();
	enemyManagerInit();
	ingameGameOverInit();
	
#ifdef PERF_FEST
	avgTime = 0.0f;
	avgTime2 = 0.0f;
#endif
	
	int x;
	for( x=0; x<SCREEN_WIDTH; x++ )
		lineBufferTemplate[ x ] = 0;//(x<<9) + (x<<1);
}

void ingame_loop()
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

#ifdef PERF_FEST
	doCameraScroll = false;
#endif
	
	if( doCameraScroll )
	{
		int scrollMax = worldWidth-96;
		if( mapScroll < scrollMax )
		{
			cameraScroll += cameraScrollSpeed;
			while( cameraScroll >= 1 )
			{
				cameraScroll -= 1;
				
				playerCameraMove( 1 );
				
				mapScroll++;
				
				GenerateTemplateGrey( 168-mapScroll, 184-mapScroll, 716-mapScroll, 748-mapScroll );
				if( mapScroll > scrollMax )
				{
					cameraScroll = scrollMax;
					doCameraScroll = false;
				}
				
				// Are we still running level functions?
				if( currentFunc < numFuncs )
				{
					//
					if( mapScroll >= levelScrollFuncs[ currentFunc ].x )
					{
						// We've passed the point of running. So run!
						levelScrollFuncs[ currentFunc ].pFunc( mapScroll );
						currentFunc++;
					}
				}
			}
		}
	}

	//
	//
	//
	int camx = mapScroll;
	mainCamera.SetWorldPosition( camx, 0 );
	playfield->SetPosition( camx, 0 );
	background->SetPosition( camx>>1, 0 );
	
	//
	playerUpdate();
	playerBulletsUpdate( mapScroll );
	explosionsUpdate();
	if( pfnIngameCallback != NULL )
		pfnIngameCallback();
	
	//
	// Tell all game objects that it is time to be rendered
	//
	gameObjectManager.Render();
	
	
	//
	// Scanline rendered
	//
	uint16* screen = screenBuffer;
	uint16* mirrorScreen = screen;

	spriteRenderer.FrameStart();
	background->FrameStart();
	playfield->FrameStart();


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
	
	Sprite* lastCollisionBullet = NULL;
	
	display.setX( 0, SCREEN_WIDTH );
	display.setY( 0, SCREEN_HEIGHT );
	display.startData();
	
	// Figures measured on a Mac, not the TinyArcade
	// Time is in nano seconds
	//
	// ---[ Times for the whole render loop ]----------------------------------------------------------------------------------------------
	// Scanline loop that is emptys: 380
	// Scanline loop with X loop that is empty: 17000
	// Scanline loop with X loop that is empty and display.writeBuffer: 51000
	// Scanline loop with X loop that does two calls to nanos(): 600000
	//
	// ---[ Times at specific points inside the loop ]-------------------------------------------------------------------------------------
	// The overhead of just calling nanos() twice in the X loop (to get start and end time): 290000
	// Timed background->RenderPixel(): 450000 (160000 when removing the overhead)
	// Timed playfield->RenderPixel, which isn't drawing anything because it is only blank tiles: 390000 (100000 when removing the overhead)
	// Timed spriteRenderer.RenderPixel: 380000 (90000 when removing the overhead)
	//
#ifdef PERF_FEST
	uint32 start = micros();
	uint32 renderTimer = 0;
#endif
	
	bool playerAlive = true;
	int iScanline = 0;
	while( iScanline < mirrorStart )
	{
		/*
		//
		if( pfnHBlankInterrupt != NULL )
			pfnHBlankInterrupt( iScanline );
		 */

		//
		// Find the correct target buffer for our double buffering code
		//
		uint32* target = lineBufferA32;
		if( lineBuffer == (uint16*)lineBufferB32 )
			target = lineBufferB32;
		
		//
		// "Clear" the background with what's in the template. The template can be used for horizontal patterns.
		//
		int i;
		for( i=0; i<SCREEN_WIDTH/2; i++ )
			target[ i ] = lineBufferTemplate32[ i ];

		// Clear collision bits for scanline
		for( i=0; i<SCREEN_WIDTH; i++ )
		{
			collisionBits[ i ] = 0;
			collisionIndices[ i+0 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+1 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+2 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+3 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+4 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+5 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+6 ] = INVALID_SPRITE_RENDERER_INDEX;
			collisionIndices[ i+7 ] = INVALID_SPRITE_RENDERER_INDEX;
		}
		
		//
		background->RenderScanline( lineBuffer, NULL );
		playfield->RenderScanline( lineBuffer, collisionBits );
		spriteRenderer.RenderScanline( lineBuffer, collisionBits, collisionIndices );

		//
		const uint8 COLLISIONMASK_BACKGROUND_PLAYER			= 1 + SPRITE_COLLISION_MASK_PLAYERSHIP;
		const uint8 COLLISIONMASK_BACKGROUND_PLAYERBULLET	= 1 + SPRITE_COLLISION_MASK_PLAYERBULLET;
		const uint8 COLLISIONMASK_PLAYER_PICKUP				= SPRITE_COLLISION_MASK_PLAYERSHIP | SPRITE_COLLISION_MASK_PICKUP;
		const uint8 COLLISIONMASK_PLAYER_ENEMY				= SPRITE_COLLISION_MASK_PLAYERSHIP | SPRITE_COLLISION_MASK_ENEMY;
		const uint8 COLLISIONMASK_PLAYER_ENEMYBULLET		= SPRITE_COLLISION_MASK_PLAYERSHIP | SPRITE_COLLISION_MASK_ENEMYBULLET;
		const uint8 COLLISIONMASK_PLAYERBULLET_ENEMY		= SPRITE_COLLISION_MASK_PLAYERBULLET | SPRITE_COLLISION_MASK_ENEMY;
		
		uint8* pixelCollisionIndices = collisionIndices;
		
		// Check out collision
		for( i=0; i<SCREEN_WIDTH; i++ )
		{
			uint8 pixelCollisionBits = collisionBits[ i ];
			if((pixelCollisionBits & COLLISIONMASK_BACKGROUND_PLAYER) == COLLISIONMASK_BACKGROUND_PLAYER )
			{
				// Only do this check if the player is still alive. So we don't register this event multiple times per rendered frame.
				if( playerAlive )
				{
					//
					// Player collided with a wall
					//
					playerAlive = false;
					playerHit( true );
					explosionsSpawn( camx+i, iScanline, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_PLAYER );
					explosionsSpawn( camx+i-4, iScanline-2, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
					explosionsSpawn( camx+i+3, iScanline+4, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
					explosionsSpawn( camx+i-1, iScanline+1, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
				}
			} else if((pixelCollisionBits & COLLISIONMASK_BACKGROUND_PLAYERBULLET) == COLLISIONMASK_BACKGROUND_PLAYERBULLET)
			{
				Sprite* bulletSprite = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_PLAYERBULLET ]);
				if( bulletSprite != lastCollisionBullet )
				{
					lastCollisionBullet = bulletSprite;
					PlayerBullet* pBullet = (PlayerBullet*)bulletSprite->owner->m_customObject;
					if((pBullet->type != PLAYERBULLET_TYPE_BOMBDEBRIS) && (pBullet->type != PLAYERBULLET_TYPE_LASER))
						playerBulletKill( bulletSprite->owner );
				}
			} else if((pixelCollisionBits & COLLISIONMASK_PLAYER_PICKUP) == COLLISIONMASK_PLAYER_PICKUP )
			{
				GameObject* pickupGO = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_PICKUP ])->owner;
				pickupTake( pickupGO );
			} else if((pixelCollisionBits & COLLISIONMASK_PLAYER_ENEMY) == COLLISIONMASK_PLAYER_ENEMY )
			{
				Sprite* enemySprite = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_ENEMY ]);
				
				if( enemySprite != lastCollisionBullet )
				{
					lastCollisionBullet = enemySprite;
					
					if( playerAlive )
					{
						if( playerHit( false ))
						{
							playerAlive = false;
							ENEMY_FROM_SPRITE( enemySprite )->Kill();
							explosionsSpawn( camx+i, iScanline, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_ENEMY );
						}
					}
				}
			} else if((pixelCollisionBits & COLLISIONMASK_PLAYER_ENEMYBULLET) == COLLISIONMASK_PLAYER_ENEMYBULLET )
			{
				Sprite* bulletSprite = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_ENEMYBULLET ]);
				
				if( bulletSprite != lastCollisionBullet )
				{
					lastCollisionBullet = bulletSprite;
					
					if( playerHit( false ))
					{
						playerAlive = false;
						explosionsSpawn( camx+i, iScanline, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_PLAYER );
						explosionsSpawn( camx+i-4, iScanline-2, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
						explosionsSpawn( camx+i+3, iScanline+4, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
						explosionsSpawn( camx+i-1, iScanline+1, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_PLAYER );
					}
				}
			} else if((pixelCollisionBits & COLLISIONMASK_PLAYERBULLET_ENEMY) == COLLISIONMASK_PLAYERBULLET_ENEMY )
			{
				Sprite* bulletSprite = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_PLAYERBULLET ]);
				
				if( bulletSprite != lastCollisionBullet )
				{
					lastCollisionBullet = bulletSprite;
					
					PlayerBullet* pBullet = (PlayerBullet*)bulletSprite->owner->m_customObject;
					if((pBullet->type != PLAYERBULLET_TYPE_BOMBDEBRIS) && (pBullet->type != PLAYERBULLET_TYPE_LASER))
						playerBulletKill( bulletSprite->owner );
					
					Sprite* enemySprite = spriteRenderer.GetSprite( pixelCollisionIndices[ SPRITE_COLLISION_INDEX_ENEMY ]);
					GameObject* enemyGO = enemySprite->owner;
					Enemy* enemy = (Enemy*)enemyGO->m_customObject;
					if( enemy->Hit())
					{
						explosionsSpawn( camx+i, iScanline, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY );
						enemyGO->SetEnabled( false );
						
						// Spawn the proper pickup
						if( enemy->SpecialFlag == ENEMY_SPECIALFLAG_DROP_DOUBLEPEW )
							pickupSpawn( PICKUP_TYPE_DOUBLEPEW, camx+i-2, iScanline-2 );
						else if( enemy->SpecialFlag == ENEMY_SPECIALFLAG_DROP_BOMB )
							pickupSpawn( PICKUP_TYPE_BOMB, camx+i-2, iScanline-2 );
						else if( enemy->SpecialFlag == ENEMY_SPECIALFLAG_DROP_LASER )
							pickupSpawn( PICKUP_TYPE_LASER, camx+i-2, iScanline-2 );
					}
				}
			}

			pixelCollisionIndices += 8;
		}

#ifdef TAGE_TARGET_MACOSX
		int x;
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			uint16 c = lineBuffer[ x ];
			uint16 nc = ((c&0x00ff)<<8) + ((c&0xff00)>>8);
			lineBuffer[ x ] = nc;
		}
		display.writeBuffer( (uint8*)lineBuffer, SCREEN_WIDTH*2 );
#else
		display.writeBufferDMA((uint8*)lineBuffer, SCREEN_WIDTH*2 );
#endif
		
		if( lineBuffer == (uint16*)lineBufferA32 )
			lineBuffer = (uint16*)lineBufferB32;
		else
			lineBuffer = (uint16*)lineBufferA32;

		/*
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
		}*/

		spriteRenderer.NextScanline( debugSpriteRenderer );
		playfield->NextScanline();
		background->NextScanline();
		
		iScanline++;
	}
	
	display.endTransfer();
	
#ifdef PERF_FEST
	uint32 end = micros();
	uint32 duration = end-start;
	float thisFrame = duration;
	avgTime = addToAverage( avgTime, thisFrame, avgTimeSamples );
	avgTime2 = addToAverage( avgTime2, (float)renderTimer, avgTimeSamples );
	
#ifdef TAGE_TARGET_MACOSX
	debugLog( "Frame render time: %6i - average: %6.0f ::: Specific timer: %6i - average: %6.0f\n", duration, avgTime, renderTimer, avgTime2 );
#else

	char buffe[ 100 ];
	display.setFont( thinPixel7_10ptFontInfo );
	display.fontColor( TS_8b_Green, TS_8b_Black );
	
	snprintf( buffe, 99, "us: %i", ((int)avgTime) );
	display.setCursor( 0, 48 );
	display.print( buffe );
	snprintf( buffe, 99, "us: %i", ((int)avgTime2) );
	display.setCursor( 0, 56 );
	display.print( buffe );
#endif
#endif

	if( playerAlive == false )
	{
		// Player died some time during this frame
		if( playerGetNumLives() == 0 )
		{
			ingameGameOverStart();
			playerDisable();
		} else
		{
			playerReset( mapScroll );
		}
	}
	
	if( gameOver )
	{
		ingameGameOverUpdate();
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
	sint32 dd = expectedFrameTime - (endTime-startTime);
	if( dd > 0 )
		delayMicroseconds( dd );
}

void ingame_exit()
{
	
}

extern void debugPrintSystems();
extern GameObject* player;

void ingame_debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		contextGotoTitleScreen();
	} else if( _trigger == 1 )
	{
		debugLog( "mapScroll=%i\n", mapScroll );
		//debugSpriteRenderer = true;
	} else if( _trigger == 2 )
	{
		debugLog( "player x=%i, y=%i\n", player->GetWorldPositionX(), player->GetWorldPositionY());
	} else if( _trigger == 3 )
	{
		extern int playerInvincibleTimer;
		playerInvincibleTimer = 60;
	} else if( _trigger == 4 )
	{
		playerPickup( PICKUP_TYPE_DOUBLEPEW );
	} else if( _trigger == 5 )
	{
		playerPickup( PICKUP_TYPE_LASER );
	} else if( _trigger == 6 )
	{
		playerPickup( PICKUP_TYPE_BOMB );
	} else if( _trigger == 7 )
	{
		spriteRenderer.debugPrintStats();
	} else if( _trigger == 8 )
	{
		expectedFrameTime = 2000;
		//enemyBulletSpawn( mapScroll+90, 32, player, FixedPoint( 0, 25 ));
	} else if( _trigger == 9 )
	{
		expectedFrameTime = 16667;
		//debugPrintSystems();
	}
}

bool ingameIsGameOver()
{
	return gameOver;
}

const int NUM_GAMEOVER_SPRITES = 8;

Sprite* gameOverSprites[ NUM_GAMEOVER_SPRITES ];
const Image* GAMEOVER_IMAGES[ NUM_GAMEOVER_SPRITES ] = {
	&sprite_gameover_g,
	&sprite_gameover_a,
	&sprite_gameover_m,
	&sprite_logo_shooter_e,
	&sprite_logo_shooter_o,
	&sprite_gameover_v,
	&sprite_logo_shooter_e,
	&sprite_logo_shooter_r,
};

int LEFT = 28;
int TOP = 17;

int GAMEOVER_COORDINATES[ NUM_GAMEOVER_SPRITES * 2 ] = {
	LEFT, TOP,
	LEFT+11, TOP,
	LEFT+21, TOP,
	LEFT+32, TOP,
	
	LEFT+1, TOP+16,
	LEFT+11, TOP+16,
	LEFT+21, TOP+16,
	LEFT+29, TOP+16,
};

int GAMEOVER_DELTAS[ NUM_GAMEOVER_SPRITES * 2 ] = {
	-2,-1,
	-1,-1,
	1,-1,
	2,-1,
	-2,1,
	-1,1,
	1,1,
	2,1,
};

void ingameGameOverInit()
{
	int i;
	for( i=0; i<NUM_GAMEOVER_SPRITES; i++ )
	{
		Sprite* sprite = spriteRenderer.AllocateSprite( GAMEOVER_IMAGES[ i ]);;
		sprite->x = GAMEOVER_COORDINATES[ (i*2)+0 ];
		sprite->y = GAMEOVER_COORDINATES[ (i*2)+1 ];
		sprite->ClrFlags( SPRITE_FLAG_ENABLED );
		sprite->sort = 10;
		gameOverSprites[ i ] = sprite;
	}
}

const int GAMEOVER_DURATION = 240;
const int GAMEOVER_DURATION_SCROLLIN = 30;
const int GAMEOVER_SCROLLIN_STOP = GAMEOVER_DURATION-GAMEOVER_DURATION_SCROLLIN;

void ingameGameOverStart()
{
	gameOver = true;
	gameOverTimer = GAMEOVER_DURATION;
	
	int i;
	for( i=0; i<NUM_GAMEOVER_SPRITES; i++ )
		gameOverSprites[ i ]->SetFlags( SPRITE_FLAG_ENABLED );
}

void ingameGameOverUpdate()
{
	int i;

	if( gameOverTimer >= GAMEOVER_SCROLLIN_STOP)
	{
		int t = gameOverTimer - GAMEOVER_SCROLLIN_STOP;

		int ri = 0;
		for( i=0; i<NUM_GAMEOVER_SPRITES; i++ )
		{
			gameOverSprites[ i ]->x = GAMEOVER_COORDINATES[ ri ] + (GAMEOVER_DELTAS[ ri ]*t); ri++;
			gameOverSprites[ i ]->y = GAMEOVER_COORDINATES[ ri ] + (GAMEOVER_DELTAS[ ri ]*t); ri++;
		}
	}

	if( gameOverTimer == GAMEOVER_SCROLLIN_STOP-1 )
		for( i=0; i<4; i++ )
			gameOverSprites[ i ]->SetFlags( SPRITE_FLAG_DRAWWHITE );
	
	if( gameOverTimer == GAMEOVER_SCROLLIN_STOP-3 )
		for( i=4; i<8; i++ )
			gameOverSprites[ i ]->SetFlags( SPRITE_FLAG_DRAWWHITE );

	if( gameOverTimer == GAMEOVER_SCROLLIN_STOP-7 )
		for( i=0; i<4; i++ )
			gameOverSprites[ i ]->ClrFlags( SPRITE_FLAG_DRAWWHITE );

	if( gameOverTimer == GAMEOVER_SCROLLIN_STOP-9 )
		for( i=4; i<8; i++ )
			gameOverSprites[ i ]->ClrFlags( SPRITE_FLAG_DRAWWHITE );
	
	gameOverTimer--;
	if( gameOverTimer == 0 )
		contextGotoTitleScreen();
}
