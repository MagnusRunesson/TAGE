//
//  EnemyManager.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Debug.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/Enemy.h"
#include "data/alldata.h"

#define NUM_ENEMIES			(40)

Enemy enemyObjects[ NUM_ENEMIES ];
int nextEnemy;

void enemyManagerInit()
{
	int i;
	for( i=0; i<NUM_ENEMIES; i++ )
	{
		Enemy* pEnemyObject = &enemyObjects[ i ];
		pEnemyObject->Reboot();
		pEnemyObject->SetDefinition( &enemy_sparrow );
		pEnemyObject->m_movementDirection.x = FixedPoint( 0, -(50-i*5) );
		pEnemyObject->m_movementDirection.y = FixedPoint( 0, -i*3 );
		pEnemyObject->pTargetGameObject->SetEnabled( false );
	}
	
	nextEnemy = 0;
}

inline void enemyIncrement()
{
	nextEnemy++;
	if( nextEnemy >= NUM_ENEMIES )
		nextEnemy = 0;
}

Enemy* enemySpawn( const EnemyDefinition* _pEnemyDefinition, int _worldX, int _worldY, const fp2d* _pMovementDirection )
{
	int safety = NUM_ENEMIES;
	
	// Allocate enemy object
	Enemy* pRet = &enemyObjects[ nextEnemy ];
	enemyIncrement();
	while( pRet->pTargetGameObject->IsEnabled() == true )
	{
		// Pick next enemy
		pRet = &enemyObjects[ nextEnemy ];
		enemyIncrement();
		
		// Make sure we don't end up in an infinite loop
		safety--;
		if( safety == 0 )
		{
			debugLog( "NOOOOOOO!\n" );
			return &enemyObjects[ 0 ];
		}
	}
	
	// Setup that enemy
	pRet->pTargetGameObject->SetEnabled( true );
	pRet->SetDefinition( _pEnemyDefinition );
	pRet->SetWorldPosition( _worldX, _worldY );
	pRet->m_movementTimer = 0;
	pRet->pTargetGameObject->GetSprite()->ClrFlags( SPRITE_FLAG_DRAWWHITE );
	pRet->AttackTimer = 0;
	
	// Set movement direction, if any
	if( _pMovementDirection )
		pRet->m_movementDirection = *_pMovementDirection;
	
	//
	return pRet;
}
