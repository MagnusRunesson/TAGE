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
#include "Engine/Debug.h"
#include "Abstraction Layer/Joypad.h"
#include "src/Ingame/Player.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/HUD.h"
#include "src/Ingame/PickupManager.h"
#include "data/alldata.h"

GameObject* player;
int playerFireRateTimerPrimary;
int playerFireIndexPrimary;
int playerFireRateTimerSecondary;
int playerFireIndexSecondary;
FixedPoint playerX;
FixedPoint playerY;
FixedPoint playerSpeed;
bool playerUpgraded;
uint8 playerNumLives;
uint8 playerInvincibleTimer;
uint8 playerWeaponPrimary;
uint8 playerWeaponSecondary;
uint8 playerRespawnY;

void playerReset( int _mapscroll )
{
	playerX = _mapscroll+10;
	playerY = playerRespawnY;
	
	playerFireRateTimerPrimary = 0;
	playerFireIndexPrimary = 0;
	
	playerFireRateTimerSecondary = 0;
	playerFireIndexSecondary = 0;
	
	playerUpgraded = false;
	playerInvincibleTimer = 60;
	playerWeaponPrimary = PLAYERWEAPON_PEW;
	playerWeaponSecondary = PLAYERWEAPON_NONE;
	
	hudSetPrimary( HUD_WEAPON_SINGLEFIRE );
	hudSetSecondary( HUD_WEAPON_NONE );
}

void playerInit( int _startX )
{
	// Create player game object
	player = gameObjectManager.CreateGameObject( &sprite_player );
	player->m_flags = GO_FLAGS_PLAYERSHIP;
	player->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_PLAYERSHIP;
	player->SetHotspot( -5, -3 );
	playerSpeed = FixedPoint( 0, 50 );

	playerRespawnY = 29;
	
	// Setup runtime data for the player
	playerReset( _startX );
	
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
void playerInput_Bomb( int _plx, int _ply );

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
	
	//
	// Do primary weapon
	//
	switch( playerWeaponPrimary )
	{
		case PLAYERWEAPON_LASER:
			playerInput_Laser( plx, ply );
			break;
			
		case PLAYERWEAPON_PEW:
			playerInput_Pew( plx, ply );
			break;
	}
	
	//
	// Do secondary weapon
	//
	switch( playerWeaponSecondary )
	{
		case PLAYERWEAPON_BOMB:
			playerInput_Bomb( plx, ply );
			break;
	}
	/*
	if( padGetPressed() & PAD_KEYMASK_SECONDARY )
		sfxPlayerPickup->PlayFromBeginning();
	 */
}

extern AudioSource* sfxPlayerFire;

void playerSetRespawnY( int _y )
{
	playerRespawnY = _y;
}

void playerInput_Pew( int _plx, int _ply )
{
	if( playerFireRateTimerPrimary > 0 )
	{
		playerFireRateTimerPrimary--;
	} else
	{
		if( padGetKeys() & PAD_KEYMASK_PRIMARY )
		{
			// Prevent shooting too often
			playerFireIndexPrimary++;
			playerFireRateTimerPrimary = FIRE_RATE_DELAY_PEW;
			
			// Spawn bullet somewhere around the player
			int x = _plx+7;
			int y = _ply+4;
			playerBulletSpawn( x, y, PLAYERBULLET_TYPE_PEW );
			
			if( playerUpgraded )
			{
				playerBulletSpawn( x+2, y-2, PLAYERBULLET_TYPE_PEW );
				sfxPlayerFire->SetData( &sfx_player_fire_double_pew );
			}
			else
			{
				sfxPlayerFire->SetData( &sfx_player_fire_pew );
			}
		} else
		{
			playerFireIndexPrimary	= 0;
		}
	}
}

void playerInput_Bomb( int _plx, int _ply )
{
	if( playerFireRateTimerSecondary > 0 )
	{
		playerFireRateTimerSecondary--;
	} else
	{
		if( padGetKeys() & PAD_KEYMASK_SECONDARY )
		{
			// Prevent shooting too often
			playerFireIndexSecondary++;
			playerFireRateTimerSecondary = FIRE_RATE_DELAY_BOMB;
			
			// Spawn bullet somewhere around the player
			int x = _plx+7;
			int y = _ply+4;
			playerBulletSpawn( x, y, PLAYERBULLET_TYPE_BOMB );
		} else
		{
			playerFireIndexSecondary = 0;
		}
	}
}

void playerInput_Laser( int _plx, int _ply )
{
	if( playerFireRateTimerPrimary > 0 )
	{
		playerFireRateTimerPrimary--;
	} else
	{
		if( padGetKeys() & PAD_KEYMASK_PRIMARY )
		{
			// Prevent shooting too often
			playerFireIndexPrimary++;
			playerFireRateTimerPrimary = FIRE_RATE_DELAY_LASER;
			
			// Spawn bullet somewhere around the player
			int x = _plx+10;
			int y = _ply+4;
			playerBulletSpawn( x, y, PLAYERBULLET_TYPE_LASER );
		} else
		{
			playerFireIndexPrimary	= 0;
		}
	}
}

void playerUpgrade()
{
	playerUpgraded = true;
	hudSetPrimary( HUD_WEAPON_DUALFIRE );
}

void playerPickup( int _type )
{
	if( _type == PICKUP_TYPE_DOUBLEPEW )
	{
		playerUpgraded = true;
		playerWeaponPrimary = PLAYERWEAPON_PEW;
		hudSetPrimary( HUD_WEAPON_DUALFIRE );
	} else if( _type == PICKUP_TYPE_BOMB )
	{
		playerWeaponSecondary = PLAYERWEAPON_BOMB;
	} else if( _type == PICKUP_TYPE_LASER )
	{
		playerWeaponPrimary = PLAYERWEAPON_LASER;
	}
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
