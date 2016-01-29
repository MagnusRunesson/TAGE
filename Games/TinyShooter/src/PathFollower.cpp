//
//  PathFollower.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 26/01/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Types.h"
#include "Engine/Math/fpmath.h"
#include "src/PathFollower.h"

PathFollower::PathFollower()
{
	m_pPathData = NULL;
}

void PathFollower::SetPath( const Path* _pPath, FixedPoint _speed, int _offsetX, int _offsetY )
{
	m_pPathData = _pPath;
	m_speed = _speed;
	m_offsetX = _offsetX;
	m_offsetY = _offsetY;

	// Start playing at the beginning
	GotoNode( 0, 0 );
}

void PathFollower::Update()
{
	m_currentInterpolationLength += m_speed;
	fp2d thisDir = m_currentTo - m_currentFrom;
	FixedPoint d = m_currentInterpolationLength / m_currentDistance;
	m_currentPosition = m_currentFrom + (thisDir * d);
}

fp2d PathFollower::GetCurrentPosition()
{
	return m_currentPosition;
}

void PathFollower::GotoNode( int _index, FixedPoint _interpolationLengthOverflow )
{
	m_currentFrom.x = m_pPathData->Points[ _index+0 ].x;
	m_currentFrom.y = m_pPathData->Points[ _index+0 ].y;
	m_currentTo.x = m_pPathData->Points[ _index+1 ].x;
	m_currentTo.y = m_pPathData->Points[ _index+1 ].y;

	m_currentDistance = 10;
	m_currentInterpolationLength = 0;
	
	//m_currentDistance = SqrDistance( m_currentTo, m_currentFrom );
	//m_currentInterpolationLength = _interpolationLengthOverflow;
}
