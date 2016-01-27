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

class GameObject;
class EnemyDefinition;

void enemyUpdatePipe( void* _pData );

class Enemy
{
public:
	GameObject* pTargetGameObject;
	uint8 Health;
	uint8 HitTimer;

	Enemy();
	
	void SetDefinition( const EnemyDefinition* _pEnemyDefinition );
	void Update();

	bool Hit();	// Return true when the enemy have reached 0 health. Return false if the enemy keeps on living.
};

#endif /* defined(__TinyShooter__Enemy__) */
