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
#include "src/Ingame/Enemy.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/Path.h"
#include "src/Ingame/PathFollower.h"
#include "src/Ingame/ExplosionManager.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/Player.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/HUD.h"
#include "src/Ingame/PickupManager.h"
#include "src/ContextManager.h"

//
Camera mainCamera;
TileRenderer* background;
TileRenderer* playfield;
int mapScroll;
FixedPoint cameraScroll;
FixedPoint cameraScrollSpeed;
AudioSource* bgm;

bool debugSpriteRenderer;
bool doCameraScroll;

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

const PathPoint testPath_nodes[] = {
	{ 0, 0 },
	{ 10, 0 },
};

const Path testPath = {
	sizeof( testPath_nodes ) / sizeof( PathPoint ),
	testPath_nodes,
};

void levelFunc10( int _x )
{
	int i;
	for( i=0; i<5; i++ )
		enemySpawn( &enemy_sparrow, _x+96+(i*3), 50-(i*2), new fp2d( FixedPoint( 0, -(40-(i*6))), FixedPoint( 0, -i*6 )));
}

void levelFunc20( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), 0 );
	int i;
	for( i=0; i<3; i++ )
		enemySpawn( &enemy_saucer_easy, _x+96+(i*14), 30, &movement );
}

void levelFunc3( int _x )
{
	fp2d movement( 0, 30 );
	int i;

	const EnemyDefinition* pDef = &enemy_dragonhead;

	for( i=0; i<5; i++ )
	{
		Enemy* pEnemy = enemySpawn( pDef, _x+96+(i*4), 30, &movement );
		pEnemy->m_movementTimer = 50 - (i*4);
		
		pDef = &enemy_dragonbody;
	}
}

void levelFuncSpawnCargo( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), FixedPoint( 0, 10 ));
	enemySpawn( &enemy_cargo, _x+96, 30, &movement )->SpecialFlag = ENEMY_SPECIALFLAG_DROP_DOUBLEPEW;
}

class LevelScrollFunc
{
public:
	int x;
	void(*pFunc)(int);
};

const LevelScrollFunc spacebaseFuncs[] = {
	{
		15,
		&levelFuncSpawnCargo,
	},
	{
		40,
		&levelFunc10,
	},
	{
		50,
		&levelFunc20,
	},
	{
		60,
		&levelFunc3
	}
};

int currentFunc;
const int numFuncs = sizeof( spacebaseFuncs ) / sizeof( LevelScrollFunc );

void ingame_setup()
{
	// Reboot all cool systems
	gameObjectManager.Reboot();
	spriteRenderer.Reboot();
	audioMixer.Reboot();
	
	currentFunc = 0;

	debugSpriteRenderer = false;

	worldWidth = tilemap_spacebase.Width * tilebank_spacebase.TileWidth;
	playfield = new TileRenderer( &tilemap_spacebase, &tilebank_spacebase );
	background = new TileRenderer( &tilemap_spacebase_background, &tilebank_spacebase );
	
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
	cameraScrollSpeed = FixedPoint( 0, 12 );

	hudInit();
	playerInit();
	pickupInit();
	
	bgm = audioMixer.GetChannel( 2 );
	
	playerBulletsInit();
	explosionsInit();
	enemyManagerInit();
	
	doCameraScroll = true;
	
	pfnHBlankInterrupt = HBlankInterrupt;
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
				if( mapScroll > scrollMax )
				{
					cameraScroll = scrollMax;
					doCameraScroll = false;
				}
				
				// Are we still running level functions?
				if( currentFunc < numFuncs )
				{
					//
					if( mapScroll >= spacebaseFuncs[ currentFunc ].x )
					{
						// We've passed the point of running. So run!
						spacebaseFuncs[ currentFunc ].pFunc( mapScroll );
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
	
	playerUpdate();
	
	playerBulletsUpdate( mapScroll );
	
	explosionsUpdate();
	
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
	
	bool playerAlive = true;
	int iScanline = 0;
	while( iScanline < mirrorStart )
	{
		int x;

		//
		if( pfnHBlankInterrupt != NULL )
			pfnHBlankInterrupt( iScanline );
		
		// Copy to screen
		for( x=0; x<SCREEN_WIDTH; x++ )
		{
			uint8 spriteCollisionMask;
			uint16 rgb = 0;
			background->RenderPixel( x, &rgb );
			bool renderedBackground = playfield->RenderPixel( x, &rgb );
			bool renderedSprite = spriteRenderer.RenderPixel( x, &rgb, &spriteCollisionMask );

			if( renderedSprite )
			{
				// A sprite was rendered on this pixel
				// Find out if:
				// 1. It was rendered on the same pixel as the background. In that case things might happen. Player death, player bullet death, etc..
				// 2. Multiple sprites was rendered on the same pixel. In that case things might happen. Player death, enemy death, player pickup, etc..
				if( renderedBackground )
				{
					// Which kind of sprites was rendered on the same pixel as the background?

					// Only do this check if the player is still alive. So we don't register this event multiple times per rendered frame.
					if( playerAlive )
					{
						//
						// Player collided with a wall
						//
						if( spriteCollisionMask & SPRITE_COLLISION_MASK_PLAYERSHIP )
						{
							playerAlive = false;
							playerHit( mapScroll, true );
							explosionsSpawn( camx+x, iScanline, EXPLOSION_TYPE_NORMAL );
							explosionsSpawn( camx+x-4, iScanline-2, EXPLOSION_TYPE_DEBRIS );
							explosionsSpawn( camx+x+3, iScanline+4, EXPLOSION_TYPE_DEBRIS );
							explosionsSpawn( camx+x-1, iScanline+1, EXPLOSION_TYPE_DEBRIS );
						}
					}
					
					//
					// Player bullet collided with a wall
					//
					if( spriteCollisionMask & SPRITE_COLLISION_MASK_PLAYERBULLET )
					{
						Sprite* bulletSprite = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_PLAYERBULLET ];
						
						if( bulletSprite != lastCollisionBullet )
						{
							lastCollisionBullet = bulletSprite;
							
							playerBulletKill( bulletSprite->owner );
						}
					}
				}
				else
				{
					//
					// Player vs. pickup
					//
					int mask = (SPRITE_COLLISION_MASK_PLAYERSHIP | SPRITE_COLLISION_MASK_PICKUP);
					if( (spriteCollisionMask & mask) == mask )
					{
						GameObject* pickupGO = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_PICKUP ]->owner;
						pickupTake( pickupGO );
					}
					
					//
					// Player vs. enemy (and enemy bullet, same collision mask)
					//
					mask = (SPRITE_COLLISION_MASK_PLAYERSHIP | SPRITE_COLLISION_MASK_ENEMY);
					if( (spriteCollisionMask & mask) == mask )
					{
						Sprite* enemySprite = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_ENEMY ];
						
						if( enemySprite != lastCollisionBullet )
						{
							lastCollisionBullet = enemySprite;
							
							if( playerHit( mapScroll, false ))
							{
								ENEMY_FROM_SPRITE( enemySprite )->Kill();
								explosionsSpawn( camx+x, iScanline, EXPLOSION_TYPE_DEBRIS );
							}
						}
					}

					//
					// Player bullet vs. enemy
					//
					mask = (SPRITE_COLLISION_MASK_PLAYERBULLET | SPRITE_COLLISION_MASK_ENEMY);
					if( (spriteCollisionMask & mask) == mask )
					{
						Sprite* bulletSprite = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_PLAYERBULLET ];
						
						if( bulletSprite != lastCollisionBullet )
						{
							lastCollisionBullet = bulletSprite;
							
							playerBulletKill( bulletSprite->owner );

							GameObject* enemyGO = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_ENEMY ]->owner;
							Enemy* enemy = (Enemy*)enemyGO->m_customObject;
							if( enemy->Hit())
							{
								explosionsSpawn( camx+x, iScanline, EXPLOSION_TYPE_NORMAL );
								enemyGO->SetEnabled( false );
								
								// Spawn double pew pickup
								if( enemy->SpecialFlag == ENEMY_SPECIALFLAG_DROP_DOUBLEPEW )
									pickupSpawn( PICKUP_TYPE_DOUBLEPEW, camx+x-2, iScanline-2 );
							}
						}
					}
				}
			}
			lineBuffer[ x ] = rgb;
		}

		// Copy from line buffer to "hardware" screen
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
		playfield->NextScanline();
		background->NextScanline();
		
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

void ingame_exit()
{
	
}

void ingame_debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		contextGotoTitleScreen();
	} else if( _trigger == 1 )
	{
		debugSpriteRenderer = true;
	} else if( _trigger == 2 )
	{
		extern int playerInvincibleTimer;
		playerInvincibleTimer = 60;
	}
}
