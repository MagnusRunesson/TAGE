//
//  EnemyMovements.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-29.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "Engine/Scene/GameObject.h"
#include "Engine/Graphics/Screen.h"
#include "Engine/Debug.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/Enemy.h"


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
	_pTarget->m_movementTimer++;
	int i = _pTarget->m_movementTimer & 0x1f;
	
	_pTarget->m_worldPosition.y = FixedPoint( 30 ) + em01_delta[ i ];
	_pTarget->m_worldPosition.x -= FixedPoint( 0, 50 );
}

void EnemyMovement_02_HalfSinus_MoveLeft( Enemy* _pTarget )
{
	_pTarget->m_movementTimer++;
	int i = _pTarget->m_movementTimer & 0x1f;

	FixedPoint s = em01_delta[ i ];
	s /= 2;
	_pTarget->m_worldPosition.y = _pTarget->m_movementDirection.y + s;
	_pTarget->m_worldPosition.x += _pTarget->m_movementDirection.x;
}

void EnemyMovement_03_DirectionThenLeft( Enemy* _pTarget )
{
	switch( _pTarget->m_movementState )
	{
		case 0:
		{
			// State 0: Move along the requested direction only
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Switch to turning slightly left
				_pTarget->m_movementTimer = 20;
				_pTarget->m_movementState = 1;
				_pTarget->m_movementDirection.y /= 2;
				_pTarget->m_movementDirection.x = _pTarget->m_movementDirection.y;
				if( _pTarget->m_movementDirection.x > 0 )
					_pTarget->m_movementDirection.x = -_pTarget->m_movementDirection.y;
			}
			break;
		}
			
		case 1:
		{
			// State 1: Move along requested direction Y and also to the left
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Switch to moving only left
				_pTarget->m_movementTimer = SCREEN_WIDTH;
				_pTarget->m_movementState = 2;
				_pTarget->m_movementDirection.x *= 2;
				_pTarget->m_movementDirection.y = 0;
			}
			break;
		}
	}
	
	//
	_pTarget->m_worldPosition += _pTarget->m_movementDirection;
}
