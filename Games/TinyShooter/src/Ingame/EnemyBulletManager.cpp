//
//  EnemyBulletManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioMixer.h"
#include "src/Ingame/EnemyBulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "data/alldata.h"

#define NUM_ENEMY_BULLETS	(4)

GameObject* enemyBullets[ NUM_ENEMY_BULLETS ];
int nextEnemyBullet;
//AudioSource* sfxPlayerFire;

void enemyBulletsInit()
{
	//
	int i;
	for( i=0; i<NUM_ENEMY_BULLETS; i++ )
	{
		GameObject* pb = gameObjectManager.CreateGameObject( &animation_enemy_bullet );
		pb->SetWorldPosition( 0, -1 );
		pb->m_flags = GO_FLAGS_ENEMYBULLET;
		pb->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_ENEMYBULLET;
		enemyBullets[ i ] = pb;
	}
	nextEnemyBullet = 0;

	// Setup sound effect for player bullets
	//sfxPlayerFire = audioMixer.GetChannel( 0 );
	//sfxPlayerFire->SetData( &sfx_player_fire_canon );
}

void enemyBulletSpawn( int _worldX, int _worldY )
{
	//
	GameObject* pb = enemyBullets[ nextEnemyBullet ];
	pb->SetWorldPosition( _worldX, _worldY );
	pb->SetEnabled( true );
	
	// Play sound effect
	//sfxPlayerFire->PlayFromBeginning();
	
	// Go to next bullet instance in a ring buffer of bullets
	nextEnemyBullet++;
	if( nextEnemyBullet >= NUM_ENEMY_BULLETS )
		nextEnemyBullet = 0;
}

void enemyBulletsUpdate( int _mapScroll )
{
	int i;
	for( i=0; i<NUM_ENEMY_BULLETS; i++ )
	{
		GameObject* bullet = enemyBullets[ i ];
		if( bullet->GetWorldPositionY() >= 0 )
		{
			int x = bullet->GetWorldPositionX()-1;
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

void enemyBulletKill( GameObject* _pb )
{
	//_pb->SetWorldPosition( 0, -1 );
	_pb->SetEnabled( false );
}
