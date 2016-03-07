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
#include "Engine/Math/fpmath.h"
#include "Engine/Debug.h"
#include "src/Ingame/EnemyMovements.h"
#include "src/Ingame/Enemy.h"
#include "src/Ingame/EnemyBulletManager.h"
#include "data/alldata.h"

extern GameObject* player;

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

void enemyHeidelbergInit( Enemy* _pEnemy )
{
	_pEnemy->Timeout = 1000;
	_pEnemy->pfnMovementUpdate = &EnemyMovement_Heidelberg;
	_pEnemy->m_movementDirection.y = 0;
	_pEnemy->m_movementDirection.x = FixedPoint( 0, -20 );
	_pEnemy->m_movementState = 0;
	_pEnemy->m_movementTimer = 240;
}

void EnemyMovement_Heidelberg( Enemy* _pTarget )
{
	switch( _pTarget->m_movementState )
	{
		case 0:
			//
			// State 0: Move forward
			//
			_pTarget->m_worldPosition += _pTarget->m_movementDirection;

			//
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 1
				_pTarget->m_movementState = 1;
				_pTarget->m_movementTimer = 30;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_anticipation );
			}
			break;
			
		case 1:
			//
			// State 1: Wait for fire
			//
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 2
				_pTarget->m_movementState = 2;
				_pTarget->m_movementTimer = 60;
				_pTarget->m_movementVar = 255;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_fire );
			}
			break;
			
		case 2:
		{
			//
			// State 2: Fire loop
			//
			uint8 newFrame = _pTarget->pTargetGameObject->GetAnimation()->FrameIndex;
			if( newFrame != _pTarget->m_movementVar )
			{
				_pTarget->m_movementVar = newFrame;
				if( newFrame == 2 )
				{
					enemyBulletSpawn( _pTarget->m_worldPosition.x.GetInteger() + 3, _pTarget->m_worldPosition.y.GetInteger() - 14, player, FixedPoint( 0, 75 ));
				}
			}

			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 2
				_pTarget->m_movementState = 3;
				_pTarget->m_movementTimer = 240;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_move );
			}
			break;
		}
			
		case 3:
			//
			// State 3: Move backwards
			//
			_pTarget->m_worldPosition -= _pTarget->m_movementDirection;
			
			//
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 4
				_pTarget->m_movementState = 4;
				_pTarget->m_movementTimer = 30;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_anticipation );
			}
			break;

		case 4:
			//
			// State 4: Anticipate 2
			//
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 2
				_pTarget->m_movementState = 5;
				_pTarget->m_movementTimer = 60;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_fire );
			}
			break;

		case 5:
		{
			//
			// State 5: Fire loop 2
			//
			uint8 newFrame = _pTarget->pTargetGameObject->GetAnimation()->FrameIndex;
			if( newFrame != _pTarget->m_movementVar )
			{
				_pTarget->m_movementVar = newFrame;
				if( newFrame == 2 )
				{
					enemyBulletSpawn( _pTarget->m_worldPosition.x.GetInteger() + 3, _pTarget->m_worldPosition.y.GetInteger() - 14, player, FixedPoint( 0, 75 ));
				}
			}
			
			_pTarget->m_movementTimer--;
			if( _pTarget->m_movementTimer == 0 )
			{
				// Goto state 0
				_pTarget->m_movementState = 0;
				_pTarget->m_movementTimer = 240;
				_pTarget->pTargetGameObject->GetAnimation()->SetSequence( &animation_enemy_heidelberg_move );
			}
			break;
		}
	}
}

void EnemyMovement_Rotate( Enemy* _pTarget )
{
	_pTarget->m_movementTimer++;
	
	int x = (fpcos( _pTarget->m_movementTimer ) >> 4);
	int y = (fpsin( _pTarget->m_movementTimer ) >> 4);
	_pTarget->m_worldPosition.x = 240 + x;
	_pTarget->m_worldPosition.y = 32 + y;
}

void enemyTurretInit( Enemy* _pTarget )
{
	_pTarget->pfnMovementUpdate = &EnemyMovement_Turret;
	_pTarget->Timeout = 1024;
	_pTarget->m_movementTimer = 3;
	
	// Set animation in idle position (pointing up)
	Animation* pAnimation = _pTarget->pTargetGameObject->GetAnimation();
	pAnimation->Stop();
	pAnimation->FrameIndex = 1;
	pAnimation->RefreshFrame();
}

void EnemyMovement_Turret( Enemy* _pTarget )
{
	int plx = player->GetWorldPositionX();
	int ply = player->GetWorldPositionY();
	int myx = _pTarget->pTargetGameObject->GetWorldPositionX();
	int myy = _pTarget->pTargetGameObject->GetWorldPositionY();
	
	int distancex = plx-myx;
	if( distancex < 0 )
		distancex = -distancex;

	int distancey = ply-myy;
	if( distancey < 0 )
		distancey = -distancey;
	
	Animation* pAnimation = _pTarget->pTargetGameObject->GetAnimation();
	if( distancex < 40 )
	{
		int frameFireOffsetX = 0;
		int frameFireOffsetY = 0;
		distancey >>= 1;
		if( distancex < distancey )
		{
			frameFireOffsetX = 1;
			frameFireOffsetY = -5;
			pAnimation->FrameIndex = 1;
			pAnimation->RefreshFrame();
		}
		else
		{
			if( plx < myx )
			{
				frameFireOffsetX = -4;
				frameFireOffsetY = -4;
				pAnimation->FrameIndex = 0;
				pAnimation->RefreshFrame();
			} else
			{
				frameFireOffsetX = 4;
				frameFireOffsetY = -4;
				pAnimation->FrameIndex = 2;
				pAnimation->RefreshFrame();
			}
		}
		
		_pTarget->m_movementTimer--;
		if( _pTarget->m_movementTimer == 0 )
		{
			int bx = _pTarget->pTargetGameObject->GetWorldPositionX() + frameFireOffsetX;
			int by = _pTarget->pTargetGameObject->GetWorldPositionY() + frameFireOffsetY;
			Enemy* pEnemyBullet = enemyBulletSpawn( bx, by, player, FixedPoint( 0, 75 ));
			pEnemyBullet->Timeout = 120;
			_pTarget->m_movementTimer = 60;
		}

	}
}

void enemySaucerStartingUpdate_BeforeStart( Enemy* _pEnemy )
{
	if( _pEnemy->m_movementTimer > 0 )
	{
		_pEnemy->m_movementTimer--;
		if( _pEnemy->m_movementTimer == 0 )
		{
			_pEnemy->m_movementDirection.x = 0;
			_pEnemy->m_movementDirection.y = FixedPoint( 0, -50 );
			_pEnemy->m_movementState = 1;
			_pEnemy->m_movementTimer = 980;
		}
	}
}

void enemySaucerStartingUpdate_FlyAway( Enemy* _pEnemy )
{
	if( _pEnemy->m_movementTimer > 0 )
	{
		_pEnemy->m_worldPosition += _pEnemy->m_movementDirection;
		_pEnemy->m_movementTimer--;
		if( _pEnemy->m_movementTimer > 950 )
		{
			debugLog("up: %i\n", _pEnemy->m_movementTimer );
		} else if( _pEnemy->m_movementTimer > 900 )
		{
			debugLog("swivel: %i\n", _pEnemy->m_movementTimer );
			_pEnemy->m_movementDirection.x -= FixedPoint( 0, 5 );
			_pEnemy->m_movementDirection.y += FixedPoint( 0, 1 );
		}
		else if( _pEnemy->m_movementTimer > 850 )
		{
			debugLog("chill until death: %i\n", _pEnemy->m_movementTimer );
		} else if( _pEnemy->m_movementTimer == 0 )
		{
			debugLog("death!\n");
			_pEnemy->Kill();
		}
	}
}

void enemySaucerStartingUpdate( Enemy* _pEnemy )
{
	switch( _pEnemy->m_movementState )
	{
		case 0:
			enemySaucerStartingUpdate_BeforeStart( _pEnemy );
			break;
			
		case 1:
			enemySaucerStartingUpdate_FlyAway( _pEnemy );
			break;
	}
}

void enemySaucerStartingInit( Enemy* _pEnemy, int _delay )
{
	_pEnemy->pfnMovementUpdate = &enemySaucerStartingUpdate;
	_pEnemy->m_movementState = 0;
	_pEnemy->Timeout = 0;
	_pEnemy->m_movementTimer = _delay;
}
