//
//  EnemyManager.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef EnemyManager_h
#define EnemyManager_h

class Enemy;
class EnemyDefinition;
class fp2d;

void enemyManagerInit();
Enemy* enemySpawn( const EnemyDefinition* _pEnemyDefinition, int _worldX, int _worldY, const fp2d* _pMovementDirection );


#endif /* EnemyManager_h */
