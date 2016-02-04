//
//  Enemy.h
//  TinyShooter
//
//  Created by Magnus Runesson on 25/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#ifndef __TinyShooter__Enemy__
#define __TinyShooter__Enemy__

#include "Engine/types.h"
#include "Engine/Math/fp2d.h"

#define ENEMY_FROM_SPRITE( spr ) ((Enemy*)(spr->owner->m_customObject))

#define ENEMY_SPECIALFLAG_EMPTY				(0)
#define ENEMY_SPECIALFLAG_DROP_DOUBLEPEW	(1)
#define ENEMY_SPECIALFLAG_INVINCIBLE		(2)

class GameObject;
class EnemyDefinition;

void enemyUpdatePipe( void* _pData );

class Enemy
{
public:
	bool isAlive;
	GameObject* pTargetGameObject;
	uint8 Health;
	uint8 HitTimer;
	uint8 SpecialFlag;
	uint8 AttackTimer;

	fp2d m_worldPosition;
	fp2d m_movementDirection;
	int m_movementTimer;

	Enemy();
	void Reboot();
	
	void SetWorldPosition( const fp2d& _worldPosition );
	void SetWorldPosition( int _x, int _y );
	void SetDefinition( const EnemyDefinition* _pEnemyDefinition );
	void Update();
	void PostRender();
	void(*pfnMovementUpdate)( Enemy* _pTarget );

	bool Hit();		// Return true when the enemy have reached 0 health. Return false if the enemy keeps on living.
	void Kill();	// Kill the enemy and return the instance to the enemy manager so a new enemy can take its place.
};

#endif /* defined(__TinyShooter__Enemy__) */
