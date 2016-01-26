//
//  PathFollower.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 26/01/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "PathFollower.h"

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
}

void PathFollower::Update()
{
	
}

fp2d PathFollower::GetCurrentPosition()
{
	return m_currentPosition;
}
