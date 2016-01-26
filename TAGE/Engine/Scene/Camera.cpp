//
//  Camera.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/Camera.h"

//
//
//
Camera* Camera::main = (Camera*)0;

//
//
//
Camera::Camera()
{
	m_worldPositionX = 0;
	m_worldPositionY = 0;
}

void Camera::SetWorldPosition( int _x, int _y )
{
	m_worldPositionX = _x;
	m_worldPositionY = _y;
}
