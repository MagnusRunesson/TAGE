//
//  GameObject.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "GameObject.h"
#include "Camera.h"

GameObject::GameObject( Image* _image )
{
	//
	m_worldPositionX = 0;
	m_worldPositionY = 0;
	
	//
	//m_image = _image;
	m_sprite = spriteRenderer.AllocateSprite( _image );
	m_imageHotspotX = 0;
	m_imageHotspotY = 0;
	//m_drawAlpha = false;
}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
	m_sprite->x = m_worldPositionX - Camera::main->GetWorldX() - m_imageHotspotX;
	m_sprite->y = m_worldPositionY - Camera::main->GetWorldY() - m_imageHotspotY;

	/*
	if( m_drawAlpha )
		m_image->DrawAlpha( x, y );
	else
		m_image->Draw( x, y );
	 */
}

void GameObject::SetWorldPosition( int _x, int _y )
{
	m_worldPositionX = _x;
	m_worldPositionY = _y;
}

int GameObject::GetWorldPositionX()
{
	return m_worldPositionX;
}

int GameObject::GetWorldPositionY()
{
	return m_worldPositionY;
}
