//
//  BulletManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef BulletManager_h
#define BulletManager_h

void playerBulletsInit();
void playerBulletSpawn( int _worldX, int _worldY );
void playerBulletsUpdate( int _mapScroll );
void playerBulletKill( GameObject* _pb );

#endif /* BulletManager_h */
