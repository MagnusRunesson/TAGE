//
//  EnemyBulletManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef EnemyBulletManager_h
#define EnemyBulletManager_h

void enemyBulletSpawn( int _worldX, int _worldY, GameObject* _pTarget, const FixedPoint& _speed );
void enemyBulletSpawn( int _worldX, int _worldY, const fp2d& _movement );

#endif /* EnemyBulletManager_h */
