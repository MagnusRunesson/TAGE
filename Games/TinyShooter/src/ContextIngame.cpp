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
#include "src/Enemy.h"
#include "src/ContextIngame.h"
#include "src/Path.h"
#include "src/PathFollower.h"
#include "src/ExplosionManager.h"
#include "src/BulletManager.h"
#include "src/Player.h"
#include "src/EnemyManager.h"

//
Camera mainCamera;
TileRenderer* background;
TileRenderer* playfield;
int mapScroll;
FixedPoint cameraScroll;
FixedPoint cameraScrollSpeed;
GameObject* testanimGO;
AudioSource* sfxPlayerPickup;
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
	bgm->SetData( &music_boss );
	bgm->PlayFromBeginning();

	int i;
	for( i=0; i<5; i++ )
		enemySpawn( &enemy_sparrow, _x+96+(i*3), 50-(i*2), new fp2d( FixedPoint( 0, -(40-(i*6))), FixedPoint( 0, -i*6 )));
}

class LevelScrollFunc
{
public:
	int x;
	void(*pFunc)(int);
};

const LevelScrollFunc spacebaseFuncs[] = {
	{
		10,
		&levelFunc10,
	},
	{
		20,
		&levelFunc20,
	}
};

int currentFunc;
const int numFuncs = 2;

void ingame_setup()
{
	currentFunc = 0;

	/*
	PathFollower janne;

	janne.SetPath( &testPath, 1, 0, 0 );

	int l;
	for( l=0; l<10; l++ )
	{
		janne.Update();
		printf( "Janne x=%i y=%i\n", janne.GetCurrentPosition().x.GetInteger(), janne.GetCurrentPosition().y.GetInteger() );
	}
	 */
	
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

	playerInit();
	
	testanimGO = gameObjectManager.CreateGameObject( &animation_pickup );
	testanimGO->SetWorldPosition( 80, 20 );
	testanimGO->GetAnimation()->Play();
	testanimGO->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PICKUP;
	
	sfxPlayerPickup = audioMixer.GetChannel( 1 );
	sfxPlayerPickup->SetData( &sfx_player_pickup );
	
	bgm = audioMixer.GetChannel( 2 );
	
	playerBulletsInit();
	explosionsInit();
	enemyManagerInit();

	int i;
	for( i=0; i<5; i++ )
		enemySpawn( &enemy_sparrow, 96+(i*3), 50-(i*2), new fp2d( FixedPoint( 0, -(40-(i*6))), FixedPoint( 0, -i*6 )));
		
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
					
					//
					// Player collided with a wall
					//
					if( spriteCollisionMask & SPRITE_COLLISION_MASK_PLAYERSHIP )
						playerReset( mapScroll );
					
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
						sfxPlayerPickup->PlayFromBeginning();
						GameObject* pickupGO = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_PICKUP ]->owner;
						pickupGO->SetWorldPosition( 0, -10 );
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
							
							ENEMY_FROM_SPRITE( enemySprite )->Kill();
							
							playerReset( mapScroll );
							
							explosionsSpawn( camx+x, iScanline, EXPLOSION_TYPE_DEBRIS );
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

void ingame_debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		debugSpriteRenderer = true;
	}
}
