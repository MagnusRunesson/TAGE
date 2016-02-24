//
//  Player.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Math/FixedPoint.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "Abstraction Layer/Joypad.h"
#include "src/Ingame/Player.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/HUD.h"
#include "data/alldata.h"

GameObject* player;
int playerFireRateTimer;
int playerFireIndex;
FixedPoint playerX;
FixedPoint playerY;
FixedPoint playerSpeed;
bool playerUpgraded;
uint8 playerNumLives;
uint8 playerInvincibleTimer;
uint8 playerEquipment;

void playerReset( int _mapscroll )
{
	playerX = _mapscroll+10;
	playerY = 29;
	playerFireRateTimer = 0;
	playerFireIndex = 0;
	playerUpgraded = false;
	playerInvincibleTimer = 60;
	playerEquipment = PLAYERBULLET_TYPE_LASER;
	
	hudSetWeapon( HUD_WEAPON_SINGLEFIRE );
}

void playerInit()
{
	// Create player game object
	player = gameObjectManager.CreateGameObject( &sprite_player );
	player->m_flags = GO_FLAGS_PLAYERSHIP;
	player->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PLAYERSHIP;
	playerSpeed = FixedPoint( 0, 50 );

	// Setup runtime data for the player
	playerReset( 0 );
	
	// Setup the first parameter for when entering the ingame context
	playerInvincibleTimer = 0;
	playerNumLives = 3;
}

void playerCameraMove( int _cameraMoveDistance )
{
	playerX += _cameraMoveDistance;
}

void playerInput_Pew( int _plx, int _ply );
void playerInput_Laser( int _plx, int _ply );

void playerUpdate()
{
	bool hide = false;
	
	if( playerInvincibleTimer > 0 )
	{
		playerInvincibleTimer--;
		if( (playerInvincibleTimer >> 2) & 1 )
		{
			hide = true;
		}
	}
	
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
	
	int plx = playerX.GetInteger();
	int ply = playerY.GetInteger();
	
	if( hide )
		player->SetWorldPosition( 0, -10 );
	else
		player->SetWorldPosition( plx, ply );
	
	if( playerEquipment == PLAYERBULLET_TYPE_LASER )
		playerInput_Laser( plx, ply );
	else
		playerInput_Pew( plx, ply );
	
	/*
	if( padGetPressed() & PAD_KEYMASK_SECONDARY )
		sfxPlayerPickup->PlayFromBeginning();
	 */
}

void playerInput_Pew( int _plx, int _ply )
{
	if( playerFireRateTimer > 0 )
	{
		playerFireRateTimer--;
	} else
	{
		if( padGetKeys() & PAD_KEYMASK_PRIMARY )
		{
			// Prevent shooting too often
			playerFireIndex++;
			playerFireRateTimer = FIRE_RATE_DELAY;
			
			// Spawn bullet somewhere around the player
			//int x = plx+7;
			//int y = ply+4;
			int x = _plx+10;
			int y = _ply+4;
			playerBulletSpawn( x, y, PLAYERBULLET_TYPE_LASER );
			
			if( playerUpgraded && ((playerFireIndex&3) == 1))
			{
				playerBulletSpawn( x+2, y-2, PLAYERBULLET_TYPE_BOMB );
			}
		} else
		{
			playerFireIndex	= 0;
		}
	}
}

PlayerBullet* playerLaser;

void playerInput_Laser( int _plx, int _ply )
{
	if( padGetPressed() & PAD_KEYMASK_PRIMARY )
	{
		int x = _plx+10;
		int y = _ply+4;
		playerLaser = playerBulletSpawn( x, y, playerEquipment );
	} else if( padGetReleased() & PAD_KEYMASK_PRIMARY )
	{
		playerBulletKill( playerLaser->pGameObject );
	}
}

void playerUpgrade()
{
	playerUpgraded = true;
	hudSetWeapon( HUD_WEAPON_DUALFIRE );
}

bool playerHit( int _mapScroll, bool _forceKill )
{
	// Assume player is not hit
	bool ret = false;
	
	if((playerInvincibleTimer == 0) || _forceKill )
	{
		// Player was hit
		playerReset( _mapScroll );
		playerNumLives--;
		hudSetNumLives( playerNumLives );
		
		ret = true;
	}
	
	return ret;
}
