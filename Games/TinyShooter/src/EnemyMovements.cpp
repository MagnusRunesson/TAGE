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

FixedPoint em01_delta[ 32 ] =
{
	FixedPoint( -4, 0 ),
	FixedPoint( -4, 0 ),
	FixedPoint( -3, -90 ),
	FixedPoint( -3, -80 ),
	FixedPoint( -3, -20 ),
	FixedPoint( -2, -50 ),
	FixedPoint( -1, -80 ),
	FixedPoint( 0, -50 ),
	FixedPoint( 0, 50 ),
	FixedPoint( 1, 80 ),
	FixedPoint( 2, 50 ),
	FixedPoint( 3, 20 ),
	FixedPoint( 3, 80 ),
	FixedPoint( 3, 90 ),
	FixedPoint( 4, 0 ),
	FixedPoint( 4, 0 ),
	FixedPoint( 4, 0 ),
	FixedPoint( 4, 0 ),
	FixedPoint( 3, 90 ),
	FixedPoint( 3, 80 ),
	FixedPoint( 3, 20 ),
	FixedPoint( 2, 50 ),
	FixedPoint( 1, 80 ),
	FixedPoint( 0, 50 ),
	FixedPoint( 0, -50 ),
	FixedPoint( -1, -80 ),
	FixedPoint( -2, -50 ),
	FixedPoint( -3, -20 ),
	FixedPoint( -3, -80 ),
	FixedPoint( -3, -90 ),
	FixedPoint( -4, 0 ),
	FixedPoint( -4, 0 ),
};

void EnemyMovement_01_Sinus_MoveLeft( Enemy* _pTarget )
{
	int i = _pTarget->m_movementTimer & 0x1f;
	
	_pTarget->m_worldPosition.y = FixedPoint( 30 ) + em01_delta[ i ];
	_pTarget->m_worldPosition.x -= FixedPoint( 0, 50 );
}
