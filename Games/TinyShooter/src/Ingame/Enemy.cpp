//
//  Enemy.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/Image.h"
#include "Engine/Graphics/Screen.h"
#include "src/Ingame/Enemy.h"
#include "src/Ingame/EnemyDefinition.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/EnemyBulletManager.h"

extern GameObject* player;

void enemyUpdatePipe( void* _pData )
{
	((Enemy*)_pData)->Update();
}

Enemy::Enemy()
{
	Reboot();
}

void Enemy::Reboot()
{
	isAlive = false;
	pTargetGameObject = NULL;
	pfnHitCallback = NULL;
	pfnMovementUpdate = NULL;
	Health = 1;
	HitTimer = 0;
	Timeout = 255;
}

void Enemy::SetDefinition( const EnemyDefinition* _pEnemyDefinition )
{
	if( pTargetGameObject == NULL )
	{
		// Create target game object
		pTargetGameObject = gameObjectManager.CreateGameObject( _pEnemyDefinition->pAnimationDefinition );
		
		pTargetGameObject->SetHotspot( 0, 0 );
		pTargetGameObject->m_flags = GO_FLAGS_ENEMY;
		pTargetGameObject->GetSprite()->collisionIndex = SPRITE_COLLISION_INDEX_ENEMY;
		pTargetGameObject->m_customObject = this;
		pTargetGameObject->m_customUpdate = enemyUpdatePipe;
	} else
	{
		// If we've already allocated a game object for this enemy we can simply modify that game object
		
		// Change the animation properly here
		pTargetGameObject->GetAnimation()->SetSequence( _pEnemyDefinition->pAnimationDefinition );
	}

	// Play the requested animation
	pTargetGameObject->GetAnimation()->Play();

	//
	Health = _pEnemyDefinition->StartHealth;
	SpecialFlag = _pEnemyDefinition->SpecialFlag;
	HitTimer = 0;
	Timeout = 255;

	pfnMovementUpdate = _pEnemyDefinition->pfnMovement;
	
	// Wake up the enemy
	isAlive = true;
}

void Enemy::Update()
{
	if( Timeout > 0 )
	{
		// If this enemy have a timeout specified then see if it is time to destroy this enemy.
		Timeout--;
		
		if( Timeout == 0 )
		{
			// Timeout reached. Disable this enemy and make room for another one.
			pTargetGameObject->SetEnabled( false );
			return;
		}
	}
	
	if( HitTimer > 0 )
	{
		HitTimer--;
		if( HitTimer == 0 )
		{
			// No more hit for the enemy
			pTargetGameObject->GetSprite()->flags &= ~SPRITE_FLAG_DRAWWHITE;
		}
	}
	
	if( AttackTimer > 0 )
	{
		AttackTimer--;
		if( AttackTimer == 0 )
		{
			// Attack the player
			enemyBulletSpawn( m_worldPosition.x.GetInteger(), m_worldPosition.y.GetInteger(), player, FixedPoint( 0, 50 ));
		}
	}
	
	if( pfnMovementUpdate != NULL )
	{
		// Update movement
		pfnMovementUpdate( this );
		pTargetGameObject->SetWorldPosition( m_worldPosition.x.GetInteger(), m_worldPosition.y.GetInteger());
	}
}

bool Enemy::Hit()
{
	// If player is invincible there is no stopping it
	if( SpecialFlag == ENEMY_SPECIALFLAG_INVINCIBLE ) return false;
	if( SpecialFlag == ENEMY_SPECIALFLAG_SPACEBASEBOSSDOOR ) return false;

	// Check death. Since Health is an unsigned value we need to
	// be careful how we subtract and check health. If we are at
	// 0 and subtract we'll end up at 255, which would be bad.
	if( Health <= 1 )
		return true;

	pTargetGameObject->GetSprite()->flags |= SPRITE_FLAG_DRAWWHITE;
	
	//
	Health--;
	HitTimer = 3;
	
	if( pfnHitCallback != NULL )
		pfnHitCallback( this );

	//
	return false;
}

void Enemy::Kill()
{
	if( SpecialFlag == ENEMY_SPECIALFLAG_SPACEBASEBOSSDOOR )
		return;
	
	pTargetGameObject->SetEnabled( false );
}

void Enemy::SetWorldPosition( const fp2d& _worldPosition )
{
	m_worldPosition = _worldPosition;
	pTargetGameObject->SetWorldPosition( m_worldPosition.x.GetInteger(), m_worldPosition.y.GetInteger());
}

void Enemy::SetWorldPosition( int _x, int _y )
{
	m_worldPosition.x = _x;
	m_worldPosition.y = _y;
	pTargetGameObject->SetWorldPosition( _x, _y );
}
