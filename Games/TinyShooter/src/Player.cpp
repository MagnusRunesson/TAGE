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
#include "src/Player.h"
#include "src/BulletManager.h"
#include "src/ContextIngame.h"
#include "data/alldata.h"

GameObject* player;
int playerFireRateTimer;
FixedPoint playerX;
FixedPoint playerY;
FixedPoint playerSpeed;
bool playerUpgraded;

void playerReset( int _mapscroll )
{
	playerX = _mapscroll+10;
	playerY = 29;
	playerFireRateTimer = 0;
	playerUpgraded = false;
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
}

void playerCameraMove( int _cameraMoveDistance )
{
	playerX += _cameraMoveDistance;
}

void playerUpdate()
{
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
			playerBulletSpawn( x, y );
			
			if( playerUpgraded )
				playerBulletSpawn( x+2, y-2 );
			
		}
	}
	
	/*
	if( padGetPressed() & PAD_KEYMASK_SECONDARY )
		sfxPlayerPickup->PlayFromBeginning();
	 */
}

void playerUpgrade()
{
	playerUpgraded = true;
}