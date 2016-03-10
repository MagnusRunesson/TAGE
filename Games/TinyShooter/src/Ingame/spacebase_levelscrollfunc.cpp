//
//  spacebase_levelscrollfunc.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-03-09.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Scene/GameObject.h"
#include "Engine/Math/fp2d.h"
#include "src/Ingame/Enemy.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/ContextIngame.h"
#include "data/alldata.h"
#include "spacebase_levelscrollfunc.h"


int sparrowSpawnPoint[] = {
	0, 0,
	-7, -2,
	-3, -5,
	-6, -9,
	-11, -8,
};

fp2d sparrowSpawnSpeed[] = {
	{ FixedPoint( 0, -30 ), FixedPoint( 0 ) },
	{ FixedPoint( 0, -30 ), FixedPoint( 0, -1 ) },
	{ FixedPoint( 0, -30 ), FixedPoint( 0, -3 ) },
	{ FixedPoint( 0, -30 ), FixedPoint( 0, -5 ) },
	{ FixedPoint( 0, -30 ), FixedPoint( 0, -6 ) },
};

void spawnSparrowsLow( int _x )
{
	int* spawnPoint = sparrowSpawnPoint;
	int i;
	for( i=0; i<5; i++ )
	{
		int xofs = *spawnPoint; spawnPoint++;
		int yofs = *spawnPoint; spawnPoint++;
		Enemy* pEnemy = enemySpawn( &enemy_sparrow, _x+107+xofs, 50+yofs, &sparrowSpawnSpeed[ i ]);
		pEnemy->Timeout = 350;
		pEnemy->pTargetGameObject->GetAnimation()->FrameIndex = i%4;
		
		// Some sparrows should attack the player
		if((i==0) || (i==3))
			pEnemy->AttackTimer = 45+(i*15);
	}
}

void spawnSpacebaseSecretPassage( int _x )
{
	Enemy* pEnemy = enemySpawn( &enemy_spacebase_secretpassage, _x+96, (12*4), NULL );
	pEnemy->Timeout = 1000;
}

void spawnStartingSaucers( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), 0 );
	int i;
	for( i=0; i<3; i++ )
	{
		Enemy* pEnemy = enemySpawn( &enemy_saucer_easy, _x+96+(i*14), 59, &movement );
		enemySaucerStartingInit( pEnemy, 160+(i*80) );
	}
}

void spawnSaucerMid( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), 0 );
	int i;
	for( i=0; i<3; i++ )
		enemySpawn( &enemy_saucer_easy, _x+96+(i*14), 30, &movement );
}

void spawnTallons( int _x, int _y )
{
	fp2d movement( FixedPoint( 0, -30 ), _y );
	int i;
	for( i=0; i<6; i++ )
	{
		Enemy* pEnemy = enemySpawn( &enemy_tallonclaw, _x+96+(i*5), 10, &movement );
		pEnemy->m_movementTimer = 50 - (i*10);
		pEnemy->Timeout += 120;
		if((i==1) || (i==5))
		{
			pEnemy->AttackTimer = 70 + (i*15);
		}
	}
}

void spawnTallonsHigh( int _x )
{
	spawnTallons( _x,  15 );
}

void spawnTallonsMid( int _x )
{
	spawnTallons( _x, 36 );
}
void spawnTallonsLow( int _x )
{
	spawnTallons( _x,  49 );
}

void spawnDoubleDragons( int _x )
{
	int i;
	
	//
	// Spawn bottom dragon
	//
	fp2d movement( 0, FixedPoint( 0, -50 ));
	const EnemyDefinition* pDef = &enemy_dragonbody;
	for( i=4; i>=0; i-- )
	{
		if( i == 0 )
			pDef = &enemy_dragonhead;
		
		Enemy* pEnemy = enemySpawn( pDef, _x+70, 60+(i*5), &movement );
		pEnemy->m_movementState = 0;
		pEnemy->m_movementTimer = 50+(i*10);
		pEnemy->pfnMovementUpdate = &EnemyMovement_03_DirectionThenLeft;
	}
	
	//
	// Spawn top dragon
	//
	movement = fp2d( 0, FixedPoint( 0, 50 ));
	pDef = &enemy_dragonbody;
	for( i=4; i>=0; i-- )
	{
		if( i == 0 )
			pDef = &enemy_dragonhead;
		
		Enemy* pEnemy = enemySpawn( pDef, _x+70, -5-(i*5), &movement );
		pEnemy->m_movementState = 0;
		pEnemy->m_movementTimer = 50+(i*10);
		pEnemy->pfnMovementUpdate = &EnemyMovement_03_DirectionThenLeft;
	}
}

void spawnDragonMid( int _x )
{
	fp2d movement( 0, 30 );
	int i;
	
	const EnemyDefinition* pDef = &enemy_dragonhead;
	
	for( i=0; i<5; i++ )
	{
		Enemy* pEnemy = enemySpawn( pDef, _x+96+(i*4), 30, &movement );
		pEnemy->m_movementTimer = 50 - (i*4);
		
		pDef = &enemy_dragonbody;
	}
}

void spawnTurrets( int _x, int _y, int _numTurrets )
{
	fp2d movement;
	int i;
	for( i=0; i<_numTurrets; i++ )
	{
		Enemy* pEnemy = enemySpawn( &enemy_turret, _x+96+(i*12), _y, &movement );
		enemyTurretInit( pEnemy );
	}
}

void spawnTurretsLow( int _x )
{
	spawnTurrets( _x, 60, 3 );
}

void spawnTurretsMid( int _x )
{
	spawnTurrets( _x, 40, 3 );
}

void spawnCargo( int _x, int _flag, int _y, fp2d& _movement )
{
	enemySpawn( &enemy_cargo, _x+96, _y, &_movement )->SpecialFlag = _flag;
}

void spawnCargoBomb( int _x )
{
	fp2d movement( FixedPoint( 0, -10 ), FixedPoint( 0, 0 ));
	spawnCargo( _x, ENEMY_SPECIALFLAG_DROP_BOMB, 50, movement );
}

void spawnCargoPew( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), FixedPoint( 0, 10 ));
	spawnCargo( _x, ENEMY_SPECIALFLAG_DROP_DOUBLEPEW, 30, movement );
}

void spawnCargoLaser( int _x )
{
	fp2d movement( FixedPoint( 0, -50 ), FixedPoint( 0, 10 ));
	spawnCargo( _x, ENEMY_SPECIALFLAG_DROP_LASER, 30, movement );
}

void spawnHeidelbergMid( int _x )
{
	Enemy* pEnemy = enemySpawn( &enemy_heidelberg, _x+96, 40, NULL );
	enemyHeidelbergInit( pEnemy );
}

void spawnHeidelbergLow( int _x )
{
	Enemy* pEnemy = enemySpawn( &enemy_heidelberg, _x+96, 60, NULL );
	enemyHeidelbergInit( pEnemy );
}

void spawnSpinloop( int _x )
{
	int i;
	for( i=0; i<10; i++ )
	{
		Enemy* pEnemy = enemySpawn( &enemy_spinloop, 0, 0, NULL );
		pEnemy->m_movementDirection.x = _x + 96 + 32 + 3;
		pEnemy->m_movementDirection.y = 32;
		pEnemy->m_movementTimer = 64 + i*16;
		pEnemy->Timeout = 1300;
		pEnemy->pTargetGameObject->GetAnimation()->FrameTime = i*7;
	}
}

const LevelScrollFunc spacebase_levelscrollfuncs[] =
{
	{
		20,
		&spawnTallonsLow,
	},
	{
		30,
		&spawnTallonsHigh,
	},
	{
		50,
		&spawnStartingSaucers
	},
	{
		55,
		&spawnCargoPew,
	},
	{
		70,
		&spawnSparrowsLow,
	},
	{
		100,
		&spawnSaucerMid,
	},
	/*
	 {
		110,
		&spawnDragonMid
	 },
	 */
	{
		120,
		&spawnSpinloop,
	},
	{
		200,
		&spawnTallonsMid,
	},
	{
		230,
		&spawnSparrowsLow,
	},
	{
		248,
		&spawnHeidelbergLow,
	},
	{
		272,
		&spawnSpacebaseSecretPassage
	},
	{
		285,
		&spawnDragonMid,
	},
	{
		290,
		&spawnTurretsMid,
	},
	{
		316,
		&spawnTallonsHigh
	},
	{
		332,
		&spawnCargoBomb,
	},
	{
		360,
		&spawnDoubleDragons
	}
};

const int spacebase_levelscrollfuncs_numfuncs = sizeof( spacebase_levelscrollfuncs ) / sizeof( LevelScrollFunc );
