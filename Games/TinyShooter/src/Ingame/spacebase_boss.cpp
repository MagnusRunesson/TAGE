//
//  spacebase_boss.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-03-14.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/GameObjectManager.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/debug.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/spacebase_boss.h"
#include "src/Ingame/Enemy.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/ExplosionManager.h"
#include "src/ContextManager.h"
#include "data/alldata.h"

//
// Settings
//
#define SBB_INITIAL_HEALTH (1)

//
// Enemies the boss can spawn
//
#define ENEMYTYPE_WALLFLOWER (0)
#define ENEMYTYPE_LASER (1)
#define ENEMYTYPE_DRAGON (2)
#define ENEMYTYPE_MISSILE (3)

//
// Patterns and positions
//
const int sbbDoorPositionX[] = {
	944,
	940,
	940,
};

const int sbbDoorPositionY[] = {
	3,
	27,
	51,
};

class CsbbEndExplosion
{
public:
	uint16 posX;
	uint16 posY;
	uint8 type;
	uint8 audioType;
	uint8 duration;
};

const CsbbEndExplosion sbbPlayerWinExplosion[] = {
	{ 934, 3, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 7 },
	{ 930, 51, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 5 },
	{ 950, 27, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 6 },
	{ 932, 38, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 10 },
	{ 945, 12, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 5 },
	{ 952, 30, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 3 },
	{ 934, 3, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 8 },
	{ 930, 51, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 6 },
	{ 950, 27, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 8 },
	{ 932, 38, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 3 },
	{ 945, 12, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 9 },
	{ 952, 30, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 8 },
	{ 934, 3, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 5 },
	{ 930, 51, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 12 },
	{ 950, 27, EXPLOSION_TYPE_DEBRIS, EXPLOSION_AUDIOTYPE_BOMB, 10 },
	{ 932, 38, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 15 },
	{ 945, 12, EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_ENEMY, 200 },
};

const uint8 sbbDoorPattern[] = {
	0,2,0,1,2,1,2,0,1,2
};

const uint8 sbbEnemyPattern[] = {
	ENEMYTYPE_MISSILE,
	ENEMYTYPE_WALLFLOWER,
	ENEMYTYPE_LASER,
	ENEMYTYPE_MISSILE,
	ENEMYTYPE_WALLFLOWER,
	ENEMYTYPE_LASER,
	ENEMYTYPE_DRAGON,
	ENEMYTYPE_WALLFLOWER,
	ENEMYTYPE_MISSILE,
	ENEMYTYPE_WALLFLOWER,
	ENEMYTYPE_MISSILE,
};

const uint8 sbbDoorPatternLength = sizeof( sbbDoorPattern );
const uint8 sbbEnemyPatternLength = sizeof( sbbEnemyPattern );
const uint8 sbbPlayerWinExplosionLength = sizeof( sbbPlayerWinExplosion ) / sizeof( CsbbEndExplosion );

//
// Game objects
//
Enemy* sbbDoor[ 3 ];
Enemy* sbbWallFlower;
Enemy* sbbWarningLights[ 3 ];

//
// Callbacks
//
void(*pfnBoss)();
void(*pfnWaitForTimerDone)();

//
// Imported functions
//
extern bool ingameIsGameOver();

//
// State variables
//
int sbbDoorIndex;
int sbbTimer;
int sbbHealth;
int sbbDoorPatternIndex;
int sbbEnemyPatternIndex;
int sbbPlayerWinExplosionIndex;
int sbbPlayerWinExplosionTimer;

//
// States
//
void sbbGotoIntro();
void sbbGotoWarningLights( int _doorIndex );
void sbbGotoOpenDoor();
void sbbGotoCloseDoor();
void sbbGotoIdleOpenDoor();
void sbbsIntro();
void sbbsWaitForAnimationCallback();
void sbbsWaitForTimer();
void sbbsPlayerWin();
void cbDoorOpenDone();
void cbDoorCloseDone();
void cbWarningLightDone();
void cbWallflowerHit( Enemy* _pEnemy );
void sbbSpawnDragon( int _x, int _y );
void sbbSpawnSparrows( int _x, int _y );
void sbbSpawnMissile( int _x, int _y );
void sbbSpawnLaser( int _x, int _y );

/******************************************************************************************************************************************
 
 Helpers
 
 ******************************************************************************************************************************************/
//
//
//
Enemy* sbbCreateDoor( int _x, int _y )
{
	Enemy* pRet = enemySpawn( &enemy_spacebase_door, _x, _y, NULL );
	pRet->Timeout = 0;
	pRet->pTargetGameObject->GetSprite()->SetSort( 2 );
	return pRet;
}

//
//
//
Enemy* sbbCreateWarningLights( int _x, int _y )
{
	Enemy* pRet = enemySpawn( &enemy_spacebase_warninglights, _x, _y, NULL );
	pRet->Timeout = 0;
	pRet->pTargetGameObject->GetSprite()->SetSort( 1 );
	return pRet;
}

//
// Public functions
//
void sbbSpawn()
{
	pfnIngameCallback = &sbbUpdate;
	
	sbbWallFlower = enemySpawn( &enemy_spacebaseboss_wallflower, sbbDoorPositionX[ 0 ] + 1, sbbDoorPositionY[ 0 ] + 2, NULL );
	sbbWallFlower->Timeout = 0;
	sbbWallFlower->pfnHitCallback = &cbWallflowerHit;
	
	sbbDoor[ 0 ] = sbbCreateDoor( sbbDoorPositionX[ 0 ], sbbDoorPositionY[ 0 ]);
	sbbDoor[ 1 ] = sbbCreateDoor( sbbDoorPositionX[ 1 ], sbbDoorPositionY[ 1 ]);
	sbbDoor[ 2 ] = sbbCreateDoor( sbbDoorPositionX[ 2 ], sbbDoorPositionY[ 2 ]);

	sbbWarningLights[ 0 ] = sbbCreateWarningLights( sbbDoorPositionX[ 0 ] + 4, sbbDoorPositionY[ 0 ]);
	sbbWarningLights[ 1 ] = sbbCreateWarningLights( sbbDoorPositionX[ 1 ] + 4, sbbDoorPositionY[ 1 ]);
	sbbWarningLights[ 2 ] = sbbCreateWarningLights( sbbDoorPositionX[ 2 ] + 4, sbbDoorPositionY[ 2 ]);
	
	sbbDoorPatternIndex = 0;
	sbbEnemyPatternIndex = 0;
	sbbHealth = SBB_INITIAL_HEALTH;
	
	pfnWaitForTimerDone = NULL;
	
	sbbGotoIntro();
}

void sbbUpdate()
{
	pfnBoss();
}

void sbbSpawnEnemy()
{
	int enemyPatternIndex = sbbEnemyPatternIndex;
	
	sbbEnemyPatternIndex++;
	if( sbbEnemyPatternIndex >= sbbEnemyPatternLength )
		sbbEnemyPatternIndex -= sbbEnemyPatternLength;

	// Disable wall flower, just in camse
	sbbWallFlower->pTargetGameObject->SetEnabled( false );
	
	int enemyType = sbbEnemyPattern[ enemyPatternIndex ];
	
	int doorX = sbbDoorPositionX[ sbbDoorIndex ];
	int doorY = sbbDoorPositionY[ sbbDoorIndex ];
	switch( enemyType )
	{
		case ENEMYTYPE_DRAGON:
			sbbSpawnDragon( doorX, doorY );
			break;

		case ENEMYTYPE_MISSILE:
			sbbSpawnMissile( doorX, doorY );
			break;

		case ENEMYTYPE_LASER:
			sbbSpawnLaser( doorX, doorY );
			break;

		case ENEMYTYPE_WALLFLOWER:
			sbbWallFlower->pTargetGameObject->SetEnabled( true );
			sbbWallFlower->SetWorldPosition( doorX+1, doorY+2 );
			break;
	}

	sbbGotoIdleOpenDoor();
}



/******************************************************************************************************************************************
 
 State helpers
 
 ******************************************************************************************************************************************/
//
// Goto the intro state
//
void sbbGotoIntro()
{
	sbbTimer = 360;
	pfnBoss = &sbbsIntro;
}

//
// This function will initiate the next door opening phase. A door opening phase consist of:
// 1. Flash warning lights
// 2. Open door
// 3. Do an enemy routine
// 3.1. Enemy 1: The red kill part
// 3.2. Enemy 2: Laser
// 3.3. Enemy 3: Missile
// 3.4. Enemy 4: Dragons
// 4. Close door
//
// When the door phase is over we idle for a bit, then open another door at random
//
void sbbStartNextDoor()
{
	// Get current index
	int currentDoorPatternIndex = sbbDoorPatternIndex;
	
	// Increment for next time
	sbbDoorPatternIndex++;
	if( sbbDoorPatternIndex >= sbbDoorPatternLength )
		sbbDoorPatternIndex -= sbbDoorPatternLength;
	
	// Fetch door index from pattern
	int doorIndex = sbbDoorPattern[ currentDoorPatternIndex ];
	sbbGotoWarningLights( doorIndex );
}


//
// Flash the warning lights that will indicate which door is about to open
//
void sbbGotoWarningLights( int _doorIndex )
{
	pfnBoss = &sbbsWaitForAnimationCallback;
	sbbDoorIndex = _doorIndex;
	Animation* pAnim = sbbWarningLights[ sbbDoorIndex ]->pTargetGameObject->GetAnimation();
	pAnim->SetSequence( &animation_spacebase_boss_warninglights_blink );
	pAnim->SetDoneCallback( &cbWarningLightDone );
	pAnim->Play();
	//sbbTimer = (18*5)-1;
}

//
// Go to Opening Door state
//
void sbbGotoOpenDoor()
{
	Animation* pAnim = sbbDoor[ sbbDoorIndex ]->pTargetGameObject->GetAnimation();
	pAnim->SetSequence( &animation_spacebase_boss_door_open );
	pAnim->SetDoneCallback( cbDoorOpenDone );
	pAnim->Play();
	//sbbTimer = (9*4)-1;
	sbbWallFlower->SpecialFlag = 0;

	// Spawn the enemy that is behind this door
	sbbSpawnEnemy();
}

void sbbGotoCloseDoor()
{
	pfnBoss = &sbbsWaitForAnimationCallback;
	Animation* pAnim = sbbDoor[ sbbDoorIndex ]->pTargetGameObject->GetAnimation();
	pAnim->SetSequence( &animation_spacebase_boss_door_close );
	pAnim->SetDoneCallback( cbDoorCloseDone );
	pAnim->Play();
	//sbbTimer = (9*1)-1;
}

void sbbGotoIdleOpenDoor()
{
	sbbTimer = 120;
	pfnWaitForTimerDone = &sbbGotoCloseDoor;
	pfnBoss = &sbbsWaitForTimer;
}

void sbbGotoWaitForTimer( int _timeout, void(*_pfnCallback)() )
{
	sbbTimer = _timeout;
	pfnWaitForTimerDone = _pfnCallback;
	pfnBoss = &sbbsWaitForTimer;

}

void sbbGotoPlayerWin()
{
	sbbPlayerWinExplosionIndex = 0;
	sbbPlayerWinExplosionTimer = 22;
	sbbTimer = 180;
	pfnBoss = &sbbsPlayerWin;
}

/******************************************************************************************************************************************
 
 Animation callbacks
 
 ******************************************************************************************************************************************/
void cbWarningLightDone()
{
	if( sbbHealth > 0 )
		sbbGotoOpenDoor();
}

void cbDoorOpenDone()
{
}

void cbDoorCloseDone()
{
	if( sbbHealth > 0 )
		sbbGotoWaitForTimer( 30, &sbbStartNextDoor );
}

void cbWallflowerHit( Enemy* _pEnemy )
{
	// Early out of the boss is already dead
	if( sbbHealth <= 0 )
		return;
	
	bool isGameOver = ingameIsGameOver();
	if( isGameOver == false )
	{
		sbbHealth--;
		if( sbbHealth == 0 )
		{
			GameObject* pEnemyGO = _pEnemy->pTargetGameObject;
			explosionsSpawn( pEnemyGO->GetWorldPositionX(), pEnemyGO->GetWorldPositionY(), EXPLOSION_TYPE_NORMAL, EXPLOSION_AUDIOTYPE_BOMB );
			pEnemyGO->SetEnabled( false );
			sbbGotoPlayerWin();
		}
		else
		{
			_pEnemy->SpecialFlag = ENEMY_SPECIALFLAG_INVINCIBLE;
			sbbGotoCloseDoor();
		}
	}
}

/******************************************************************************************************************************************
 
 The states
 
******************************************************************************************************************************************/
//
// Intro state
//
void sbbsIntro()
{
	sbbTimer--;
	if( sbbTimer == 0 )
		sbbStartNextDoor();
}

void sbbsWaitForAnimationCallback()
{
	
}

void sbbsWaitForTimer()
{
	sbbTimer--;
	if( sbbTimer <= 0 )
	{
		if( pfnWaitForTimerDone != NULL )
			pfnWaitForTimerDone();
	}
}

void sbbsPlayerWin()
{
	sbbPlayerWinExplosionTimer--;
	if( sbbPlayerWinExplosionTimer == 0 )
	{
		// Fetch the current data
		const CsbbEndExplosion* pExplosionData = &sbbPlayerWinExplosion[ sbbPlayerWinExplosionIndex ];
		GameObject* pExplosion = explosionsSpawn( pExplosionData->posX, pExplosionData->posY, pExplosionData->type, pExplosionData->audioType );
		pExplosion->GetSprite()->SetSort( 3 );
		
		// Go to next explosion definition
		sbbPlayerWinExplosionIndex++;
		if( sbbPlayerWinExplosionIndex == sbbPlayerWinExplosionLength )
			sbbPlayerWinExplosionIndex = 0;
		
		// Wait for next explosion
		sbbPlayerWinExplosionTimer = pExplosionData->duration;
		debugLog("Wait for %i frames\n", sbbPlayerWinExplosionTimer );
	}
	
	sbbTimer--;
	if( sbbTimer <= 0 )
	{
		contextGotoWinScreen();
	}
}

/******************************************************************************************************************************************

 Spawning enemies
 
 ******************************************************************************************************************************************/
void sbbSpawnDragon( int _x, int _y )
{
	// Offset from door position
	_x += 3;
	_y += 2;
	
	fp2d movement( FixedPoint( 0, -25 ), _y );
	int i;
	
	const EnemyDefinition* pDef = &enemy_dragonhead;
	
	for( i=0; i<5; i++ )
	{
		Enemy* pEnemy = enemySpawn( pDef, _x+(i*4), _y, &movement );
		pEnemy->m_movementTimer = 50 - (i*4);
		pEnemy->pfnMovementUpdate = &EnemyMovement_02_HalfSinus_MoveLeft;
		
		pDef = &enemy_dragonbody;
	}
}

void sbbSpawnMissile( int _x, int _y )
{
	fp2d movement( FixedPoint( 0, -150 ), 0 );
	Enemy* pEnemy = enemySpawn( &enemy_missile, _x+40, _y+4, &movement );
	pEnemy->m_movementTimer = 50;
}

void sbbSpawnLaser( int _x, int _y )
{
	Enemy* pEnemy = enemySpawn( &enemy_spacebase_boss_laser, _x+2, _y+4, NULL );
	pEnemy->Timeout = 120;
}
