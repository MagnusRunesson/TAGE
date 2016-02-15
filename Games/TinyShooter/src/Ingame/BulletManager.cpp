//
//  BulletManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "src/Ingame/BulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "data/alldata.h"

#define NUM_PLAYER_BULLETS	(14)

GameObject* playerBullets[ NUM_PLAYER_BULLETS ];
int nextPlayerBullet;
AudioSource* sfxPlayerFire;

void playerBulletsInit()
{
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

	// Setup sound effect for player bullets
	sfxPlayerFire = audioMixer.GetChannel( 0 );
	sfxPlayerFire->SetData( &sfx_player_fire_canon );
}

void playerBulletSpawn( int _worldX, int _worldY )
{
	//
	GameObject* pb = playerBullets[ nextPlayerBullet ];
	pb->SetWorldPosition( _worldX, _worldY );
	pb->SetEnabled( true );
	
	/*
	// Play sound effect
	sfxPlayerFire->PlayFromBeginning();
	 */
	
	// Go to next bullet instance in a ring buffer of bullets
	nextPlayerBullet++;
	if( nextPlayerBullet >= NUM_PLAYER_BULLETS )
		nextPlayerBullet = 0;
}

void playerBulletsUpdate( int _mapScroll )
{
	int i;
	for( i=0; i<NUM_PLAYER_BULLETS; i++ )
	{
		GameObject* bullet = playerBullets[ i ];
		if( bullet->GetWorldPositionY() >= 0 )
		{
			int x = bullet->GetWorldPositionX()+2;
			if( x >= _mapScroll+99 )
			{
				bullet->SetWorldPosition( 0, -1 );
			}
			else
			{
				bullet->SetWorldPosition( x, bullet->GetWorldPositionY());
			}
		}
	}
}

void playerBulletKill( GameObject* _pb )
{
	//_pb->SetWorldPosition( 0, -1 );
	_pb->SetEnabled( false );
}
