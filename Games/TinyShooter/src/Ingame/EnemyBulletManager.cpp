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
#include "Engine/Math/fp2d.h"
#include "src/Ingame/EnemyBulletManager.h"
#include "src/Ingame/ContextIngame.h"
#include "src/Ingame/EnemyManager.h"
#include "data/alldata.h"

void enemyBulletSpawn( int _worldX, int _worldY, GameObject* _pTarget )
{
	fp2d here( _worldX, _worldY );
	fp2d there( _pTarget->GetWorldPositionX(), _pTarget->GetWorldPositionY());
	fp2d dir = there-here;
	FixedPoint l = dir.Length();
	enemyBulletSpawn( _worldX, _worldY, dir );
}

void enemyBulletSpawn( int _worldX, int _worldY, const fp2d& _movement )
{
	enemySpawn( &enemy_bullet, _worldX, _worldY, &_movement );
}
