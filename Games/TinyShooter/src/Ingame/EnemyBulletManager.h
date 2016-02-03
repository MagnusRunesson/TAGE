//
//  EnemyBulletManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef EnemyBulletManager_h
#define EnemyBulletManager_h

void enemyBulletsInit();
void enemyBulletSpawn( int _worldX, int _worldY );
void enemyBulletsUpdate( int _mapScroll );
void enemyBulletKill( GameObject* _pb );

#endif /* EnemyBulletManager_h */
