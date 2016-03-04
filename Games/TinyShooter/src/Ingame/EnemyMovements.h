//
//  EnemyMovements.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef EnemyMovements_h
#define EnemyMovements_h

class Enemy;

extern void enemyHeidelbergInit( Enemy* _pEnemy );
extern void enemyTurretInit( Enemy* _pTarget );

extern void EnemyMovement_00_FollowDirection( Enemy* _pTarget );
extern void EnemyMovement_01_Sinus_MoveLeft( Enemy* _pTarget );
extern void EnemyMovement_02_HalfSinus_MoveLeft( Enemy* _pTarget );
extern void EnemyMovement_03_DirectionThenLeft( Enemy* _pTarget );
extern void EnemyMovement_Heidelberg( Enemy* _pTarget );
extern void EnemyMovement_Rotate( Enemy* _pTarget );
extern void EnemyMovement_Turret( Enemy* _pTarget );

#endif /* EnemyMovements_h */
