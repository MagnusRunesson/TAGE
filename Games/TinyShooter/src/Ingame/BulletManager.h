//
//  BulletManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef BulletManager_h
#define BulletManager_h

#include "Engine/Math/fp2d.h"

class PlayerBullet
{
public:
	uint8 type;
	uint8 timeout;
	Animation* pAnimation;
	GameObject* pGameObject;
	fp2d vec0;
	fp2d vec1;
};

#define PLAYERBULLET_TYPE_PEW			(0)
#define PLAYERBULLET_TYPE_BOMB			(1)
#define PLAYERBULLET_TYPE_BOMBDEBRIS	(2)

void playerBulletsInit();
void playerBulletSpawn( int _worldX, int _worldY, int _type );
void playerBulletsUpdate( int _mapScroll );
void playerBulletKill( GameObject* _pb );

#endif /* BulletManager_h */
