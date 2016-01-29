//
//  Explosions.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef ExplosionManager_h
#define ExplosionManager_h

#define EXPLOSION_TYPE_NORMAL		(0)
#define EXPLOSION_TYPE_DEBRIS		(1)

void explosionsInit();
void explosionsUpdate();
void explosionsSpawn( int _worldX, int _worldY, int _explosionType );

#endif /* Explosions_h */
