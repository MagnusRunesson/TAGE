//
//  TinyRaceCar.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "TinyRaceCar.h"
#include "AllData.h"
#include "screen.h"
#include "joypad.h"
#include "bithelpers.h"
#include "fpmath.h"
#include "Camera.h"

TinyRaceCar::TinyRaceCar() : GameObject( &testcar )
{
	// Unit is pixels per second
	m_acceleration = FixedPoint( 1, 0 );
	m_maxSpeed = FixedPoint( 30 );
	m_speedDamping = FixedPoint( 0, 75 );
	m_brake = FixedPoint( 2, 0 );
	m_turn = FixedPoint( 135, 0 );

	// Inverted frames per second, to multiply all the units that are expressed in seconds so they are expressed in frames
	FixedPoint secondsPerFrame = FixedPoint( 0, 2 );
	m_acceleration *= secondsPerFrame;
	m_brake *= secondsPerFrame;
	m_maxSpeed *= secondsPerFrame;
	m_speedDamping *= secondsPerFrame;
	m_turn *= secondsPerFrame;

	/*
	int w = 5;
	int h = 5;
	int mx = SCREEN_WIDTH - w;
	int my = SCREEN_HEIGHT - h;
	
	sint8 padX, padY;
	uint16 keys = padGet( &padX, &padY );
	
	FixedPoint spx = padX;
	spx *= fpSpeed;
	FixedPoint spy = padY;
	spy *= fpSpeed;
	
	fpX += spx;
	fpY += spy;
	 */
	
	m_drawAngle = 0;
}

TinyRaceCar::~TinyRaceCar()
{
	
}

void TinyRaceCar::Update()
{
	DoSpeed();
	DoTurning();
}

void TinyRaceCar::DoSpeed()
{
	uint8 keys = padGetKeys();
	if( HasBit( keys, PAD_KEYMASK_SECONDARY ))
	{
		if( m_speed > 0 )
		{
			m_speed -= m_brake;
			if( m_speed < 0 )
				m_speed = 0;
		}
	}
	else if( HasBit( keys, PAD_KEYMASK_PRIMARY ))
	{
		m_speed += m_acceleration;
		if( m_speed > m_maxSpeed )
			m_speed = m_maxSpeed;
	} else
	{
		if( m_speed > 0 )
		{
			m_speed -= m_speedDamping;
			if( m_speed < 0 )
				m_speed = 0;
		}
	}

	FixedPoint ax = m_direction.x;
	FixedPoint ay = m_direction.y;
	ax *= m_speed;
	ay *= m_speed;
	fp2d add = fp2d( ax, ay );
	m_position += add;
	
	SetWorldPosition( m_position.x.GetInteger(), m_position.y.GetInteger());
}

void TinyRaceCar::DoTurning()
{
	sint8 x = padGetX();

	FixedPoint turnThisFrame = m_turn;
	turnThisFrame *= x;

	m_angle += turnThisFrame;
	
	int a = m_angle.GetInteger();
	m_drawAngle = 0;
	while( a >= 85 )
	{
		a -= 90;
		m_drawAngle += 0x40;
	}

	while( a < -2 )
	{
		a += 90;
		m_drawAngle -= 0x40;
	}

	m_imageHotspotX = 4;
	m_imageHotspotY = 4;
	
	if((a >= -5) && (a < 5))
	{
		m_image = &tinyracecar_0;
	}
	if((a >= 5) && (a < 15))
	{
		m_image = &tinyracecar_10;
	}
	if((a >= 15) && (a < 25))
	{
		m_image = &tinyracecar_20;
	}
	if((a >= 25) && (a < 35))
	{
		m_image = &tinyracecar_30;
	}
	if((a >= 35) && (a < 45))
	{
		m_image = &tinyracecar_40;
	}
	if((a >= 45) && (a < 55))
	{
		m_image = &tinyracecar_50;
	}
	if((a >= 55) && (a < 65))
	{
		m_image = &tinyracecar_60;
	}
	if((a >= 65) && (a < 75))
	{
		m_image = &tinyracecar_70;
	}
	if((a >= 75) && (a < 85))
	{
		m_image = &tinyracecar_80;
	}

	FixedPoint fpangle = m_angle;
	fpangle *= FixedPoint( 0, 71 );
	int fpa = fpangle.GetInteger()-0x40;
	
	m_direction.x = fpcos( fpa );
	m_direction.x /= 256;
	m_direction.y = fpsin( fpa );
	m_direction.y /= 256;
}

void TinyRaceCar::Render()
{
	int x = m_worldPositionX - Camera::main->GetWorldX() - m_imageHotspotX;
	int y = m_worldPositionY - Camera::main->GetWorldY() - m_imageHotspotY;
	
	m_image->DrawRotatedAlpha( x, y, m_drawAngle, 0x0100 );
}

void TinyRaceCar::SetPosition( int _x, int _y )
{
	m_position.x = _x;
	m_position.y = _y;
	SetWorldPosition( _x, _y );
}