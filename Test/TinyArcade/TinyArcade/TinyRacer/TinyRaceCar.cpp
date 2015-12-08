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

TinyRaceCar::TinyRaceCar() : GameObject( &testcar )
{
	// Unit is pixels per second
	m_acceleration = FixedPoint( 1, 0 );
	m_maxSpeed = FixedPoint( 10 );
	m_speedDamping = FixedPoint( 0, 25 );
	m_turn = FixedPoint( 90, 0 );

	// Inverted frames per second, to multiply all the units that are expressed in seconds so they are expressed in frames
	FixedPoint secondsPerFrame = FixedPoint( 0, 2 );
	m_acceleration *= secondsPerFrame;
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
	
}

void TinyRaceCar::Render()
{
	//GameObject::Render();
	//screenBuffer[ m_worldPositionY * SCREEN_WIDTH + m_worldPositionX ] = 0x0000;
	
	m_image->DrawRotatedAlpha( m_worldPositionX, m_worldPositionY, m_drawAngle, 0x0100 );
}