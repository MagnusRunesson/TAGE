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
#include "Animation.h"
#include "AudioMixer.h"

// Project specifics
#include "alldata.h"

#define NUM_PLAYER_BULLETS	(10)
#define NUM_EXPLOSIONS		(10)
#define NUM_ENEMIES			(10)

#define FIRE_RATE_DELAY (10)

#define GO_FLAGS_UNIMPORTANT	(0)
#define GO_FLAGS_PLAYERSHIP		(1)
#define GO_FLAGS_PLAYERBULLET	(2)
#define GO_FLAGS_ENEMY			(3)

#define SPRITE_COLLISION_INDEX_UNIMPORTANT	(0)
#define SPRITE_COLLISION_INDEX_PLAYERSHIP	(1)
#define SPRITE_COLLISION_INDEX_PLAYERBULLET	(2)
#define SPRITE_COLLISION_INDEX_ENEMY		(3)
#define SPRITE_COLLISION_INDEX_PICKUP		(4)

#define SPRITE_COLLISION_MASK_UNIMPORTANT	(1<<SPRITE_COLLISION_INDEX_UNIMPORTANT)
#define SPRITE_COLLISION_MASK_PLAYERSHIP	(1<<SPRITE_COLLISION_INDEX_PLAYERSHIP)
#define SPRITE_COLLISION_MASK_PLAYERBULLET	(1<<SPRITE_COLLISION_INDEX_PLAYERBULLET)
#define SPRITE_COLLISION_MASK_ENEMY			(1<<SPRITE_COLLISION_INDEX_ENEMY)
#define SPRITE_COLLISION_MASK_PICKUP		(1<<SPRITE_COLLISION_INDEX_PICKUP)

//
Camera mainCamera;
TileRenderer* background;
TileRenderer* playfield;
int mapScroll;
FixedPoint cameraScroll;
FixedPoint cameraScrollSpeed;
GameObject* player;
GameObject* playerBullets[ NUM_PLAYER_BULLETS ];
GameObject* testanimGO;
AudioSource* sfxPlayerFire;
AudioSource* sfxPlayerPickup;

GameObject* explosions[ NUM_EXPLOSIONS ];
int nextExplosion;

GameObject* enemies[ NUM_ENEMIES ];
int nextEnemy;

int nextPlayerBullet;
int playerFireRateTimer;
FixedPoint playerX;
FixedPoint playerY;
FixedPoint playerSpeed;

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

void ResetPlayer()
{
	playerX = mapScroll+10;
	playerY = 29;
}

void ingame_setup()
{
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

	// Create player game object
	player = gameObjectManager.CreateGameObject( &sprite_player );
	player->m_flags = GO_FLAGS_PLAYERSHIP;
	player->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PLAYERSHIP;
	ResetPlayer();
	playerSpeed = FixedPoint( 0, 50 );
	
	testanimGO = gameObjectManager.CreateGameObject( &animation_pickup );
	testanimGO->SetWorldPosition( 80, 20 );
	testanimGO->GetAnimation()->Play();
	testanimGO->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PICKUP;
	
	sfxPlayerFire = audioMixer.GetChannel( 0 );
	sfxPlayerFire->SetData( &sfx_player_fire_canon );
	
	sfxPlayerPickup = audioMixer.GetChannel( 1 );
	sfxPlayerPickup->SetData( &sfx_player_pickup );
	
	//
	int i;
	for( i=0; i<NUM_PLAYER_BULLETS; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &sprite_pb_01 );
		pb->SetWorldPosition( 0, -1 );
		pb->m_flags = GO_FLAGS_PLAYERBULLET;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PLAYERBULLET;
		playerBullets[ i ] = pb;
	}

	nextPlayerBullet = 0;

	
	//
	//
	//
	for( i=0; i<NUM_EXPLOSIONS; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &animation_explosion_big );
		pb->SetWorldPosition( 0, -10 );
		pb->SetHotspot( 5, 4 );
		pb->m_flags = GO_FLAGS_UNIMPORTANT;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_UNIMPORTANT;
		explosions[ i ] = pb;
	}
	
	nextExplosion = 0;

	
	for( i=0; i<NUM_ENEMIES; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &animation_enemy_saucer );
		pb->SetWorldPosition( 100+(i*20), 30 );
		pb->SetHotspot( 0, 0 );
		pb->GetAnimation()->Play();
		pb->m_flags = GO_FLAGS_ENEMY;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_ENEMY;
		enemies[ i ] = pb;
	}
	
	nextEnemy = 0;
	

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
				
				playerX += 1;
				mapScroll++;
				
				if( mapScroll > scrollMax )
				{
					cameraScroll = scrollMax;
					doCameraScroll = false;
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
	int ix = padGetX();
	if( ix != 0 )
	{
		FixedPoint x = ix;
		x *= playerSpeed;
		playerX += x;
	}

	int iy = padGetY();
	if( iy != 0 )
	{
		FixedPoint y = iy;
		y *= playerSpeed;
		playerY += y;
	}
	
	player->SetWorldPosition( playerX.GetInteger(), playerY.GetInteger());

	if( playerFireRateTimer > 0 )
	{
		playerFireRateTimer--;
	} else
	{
		if( padGetKeys() & PAD_KEYMASK_PRIMARY )
		{
			// Prevent shooting too often
			playerFireRateTimer = FIRE_RATE_DELAY;
			
			// Spawn bullet somewhere around the player
			int x = player->GetWorldPositionX()+7;
			int y = player->GetWorldPositionY()+4;
			playerBullets[ nextPlayerBullet ]->SetWorldPosition( x, y );
			
			// Play sound effect
			sfxPlayerFire->PlayFromBeginning();
			
			// Go to next bullet instance in a ring buffer of bullets
			nextPlayerBullet++;
			if( nextPlayerBullet >= NUM_PLAYER_BULLETS )
				nextPlayerBullet = 0;
		}
	}
	
	if( padGetPressed() & PAD_KEYMASK_SECONDARY )
		sfxPlayerPickup->PlayFromBeginning();
	
	int i;
	for( i=0; i<NUM_PLAYER_BULLETS; i++ )
	{
		GameObject* bullet = playerBullets[ i ];
		if( bullet->GetWorldPositionY() >= 0 )
		{
			int x = bullet->GetWorldPositionX()+2;
			if( x >= mapScroll+99 )
			{
				bullet->SetWorldPosition( 0, -1 );
			}
			else
			{
				bullet->SetWorldPosition( x, bullet->GetWorldPositionY());
			}
		}
	}
	
	for( i=0; i<NUM_EXPLOSIONS; i++ )
	{
		GameObject* exp = explosions[ i ];
		if( exp->GetAnimation()->IsPlaying == false )
		{
			exp->SetWorldPosition( 0, -10 );
		}
	}
	
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
						ResetPlayer();
					
					//
					// Player bullet collided with a wall
					//
					if( spriteCollisionMask & SPRITE_COLLISION_MASK_PLAYERBULLET )
					{
						Sprite* bulletSprite = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_PLAYERBULLET ];
						
						if( bulletSprite != lastCollisionBullet )
						{
							lastCollisionBullet = bulletSprite;
							
							GameObject* bulletGO = bulletSprite->owner;
							bulletGO->SetWorldPosition( 0, -1 );
							
							GameObject* exp = explosions[ nextExplosion ];
							nextExplosion++;
							if( nextExplosion >= NUM_EXPLOSIONS )
								nextExplosion -= NUM_EXPLOSIONS;
							
							exp->SetWorldPosition( camx+x, iScanline );
							exp->GetAnimation()->Reset();
							exp->GetAnimation()->Play();
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
							
							GameObject* enemyGO = enemySprite->owner;
							enemyGO->SetWorldPosition( 0, -10 );
							
							ResetPlayer();
							
							GameObject* exp = explosions[ nextExplosion ];
							nextExplosion++;
							if( nextExplosion >= NUM_EXPLOSIONS )
								nextExplosion -= NUM_EXPLOSIONS;
							
							exp->SetWorldPosition( camx+x, iScanline );
							exp->GetAnimation()->Reset();
							exp->GetAnimation()->Play();
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
							
							GameObject* bulletGO = bulletSprite->owner;
							bulletGO->SetWorldPosition( 0, -1 );
							
							GameObject* enemyGO = spriteRenderer.m_collisionSprites[ SPRITE_COLLISION_INDEX_ENEMY ]->owner;
							enemyGO->SetWorldPosition( 0, -30 );
							
							GameObject* exp = explosions[ nextExplosion ];
							nextExplosion++;
							if( nextExplosion >= NUM_EXPLOSIONS )
								nextExplosion -= NUM_EXPLOSIONS;
							
							exp->SetWorldPosition( camx+x, iScanline );
							exp->GetAnimation()->Reset();
							exp->GetAnimation()->Play();
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
