//
//  BulletManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef BulletManager_h
#define BulletManager_h

#define PLAYERBULLET_TYPE_PEW			(0)
#define PLAYERBULLET_TYPE_BOMB			(1)

void playerBulletsInit();
void playerBulletSpawn( int _worldX, int _worldY, int _type );
void playerBulletsUpdate( int _mapScroll );
void playerBulletKill( GameObject* _pb );

#endif /* BulletManager_h */
