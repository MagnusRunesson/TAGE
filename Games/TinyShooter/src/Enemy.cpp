//
//  Enemy.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "src/Enemy.h"
#include "src/EnemyDefinition.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "src/ContextIngame.h"

void enemyUpdatePipe( void* _pData )
{
	((Enemy*)_pData)->Update();
}

Enemy::Enemy()
{
	isAlive = false;
	pTargetGameObject = NULL;
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
	HitTimer = 0;
	pfnMovementUpdate = _pEnemyDefinition->pfnMovement;
	
	// Wake up the enemy
	isAlive = true;
}

void Enemy::Update()
{
	if( HitTimer > 0 )
	{
		HitTimer--;
		if( HitTimer == 0 )
		{
			// No more hit for the enemy
			pTargetGameObject->GetSprite()->flags &= ~SPRITE_FLAG_DRAWWHITE;
		}
	}
	
	// Update movement
	m_movementTimer++;
	pfnMovementUpdate( this );
	pTargetGameObject->SetWorldPosition( m_worldPosition.x.GetInteger(), m_worldPosition.y.GetInteger());
}

bool Enemy::Hit()
{
	// Check death. Since Health is an unsigned value we need to
	// be careful how we subtract and check health. If we are at
	// 0 and subtract we'll end up at 255, which would be bad.
	if( Health <= 1 )
		return true;
	
	pTargetGameObject->GetSprite()->flags |= SPRITE_FLAG_DRAWWHITE;
	
	//
	Health--;
	HitTimer = 3;
	
	//
	return false;
}

void Enemy::Kill()
{
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
