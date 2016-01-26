//
//  Enemy.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Enemy.h"
#include "EnemyDefinition.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ContextIngame.h"

void enemyUpdatePipe( void* _pData )
{
	((Enemy*)_pData)->Update();
}

Enemy::Enemy()
{
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

	}

	// Play the requested animation
	pTargetGameObject->GetAnimation()->Play();

	Health = _pEnemyDefinition->StartHealth;
	HitTimer = 0;
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
