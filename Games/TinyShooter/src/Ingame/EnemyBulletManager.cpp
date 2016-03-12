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
#include "Engine/Math/FixedPoint.h"
#include "Engine/Graphics/Animation.h"
#include "Engine/Math/fp2d.h"
#include "Engine/Math/fpmath.h"
#include "src/Ingame/EnemyBulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/EnemyManager.h"
#include "src/Ingame/Enemy.h"
#include "data/alldata.h"

Enemy* enemyBulletSpawn( int _worldX, int _worldY, GameObject* _pTarget, const FixedPoint& _speed )
{
	fp2d there( _pTarget->GetWorldPositionX(), _pTarget->GetWorldPositionY());
	return enemyBulletSpawn( _worldX, _worldY, there, _speed );
}

Enemy* enemyBulletSpawn( int _worldX, int _worldY, const fp2d& _targetPosition, const FixedPoint& _speed )
{
	fp2d here( _worldX, _worldY );
	fp2d dir = _targetPosition-here;
	
	dir.Normalize();
	dir *= _speed;
	
	return enemyBulletSpawn( _worldX, _worldY, dir );
}

Enemy* enemyBulletSpawn( int _worldX, int _worldY, const fp2d& _movement )
{
	Enemy* pEnemy = enemySpawn( &enemy_bullet, _worldX, _worldY, &_movement );
	pEnemy->pTargetGameObject->GetAnimation()->Play();
	return pEnemy;
	
}
