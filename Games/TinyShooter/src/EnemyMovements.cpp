//
//  EnemyMovements.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Engine/Scene/GameObject.h"
#include "src/EnemyMovements.h"
#include "src/Enemy.h"


void EnemyMovement_00_FollowDirection( Enemy* _pTarget )
{
	_pTarget->m_worldPosition += _pTarget->m_movementDirection;
}
