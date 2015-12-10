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
	m_maxSpeed = FixedPoint( 60 );
	m_speedDamping = FixedPoint( 0, 75 );
	m_brake = FixedPoint( 2, 0 );
	m_turn = FixedPoint( 90, 0 );

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
	while( a >= 79 )
	{
		a -= 90;
		m_drawAngle += 0x40;
	}

	while( a < -12 )
	{
		a += 90;
		m_drawAngle -= 0x40;
	}
	
	if((a >= -12) && (a < 13))
	{
		m_image = &testcar;
		m_imageHotspotX = 5;
		m_imageHotspotY = 3;
	}
	if((a >= 13) && (a < 35))
	{
		m_image = &carrot_1;
		m_imageHotspotX = 6;
		m_imageHotspotY = 5;
	}
	if((a >= 35) && (a < 56))
	{
		m_image = &carrot_2;
		m_imageHotspotX = 6;
		m_imageHotspotY = 6;
	}
	if((a >= 56) && (a < 79))
	{
		m_image = &carrot_3;
		m_imageHotspotX = 5;
		m_imageHotspotY = 6;
	}

	FixedPoint fpangle = m_angle;
	fpangle *= FixedPoint( 0, 71 );
	int fpa = fpangle.GetInteger();
	
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