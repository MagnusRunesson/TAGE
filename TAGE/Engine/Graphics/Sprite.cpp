//
//  Sprite.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Graphics/Sprite.h"
#include "Engine/Graphics/Image.h"

Sprite::Sprite()
{
	Reboot();
}

void Sprite::Reboot()
{
	x = 127;
	y = 127;
	flags = 0;
	image = NULL;
}

void Sprite::SetRotation( int _rotation )
{
	ClrFlags( SPRITE_FLAG_ROTATE_MASK );
	SetFlags( _rotation << SPRITE_FLAG_ROTATE_BASE );
}

//
// Refresh everything needed for rendering sprites, such as refresing their on screen bounds.
//
void Sprite::PreRender()
{
	int rotation = (flags & SPRITE_FLAG_ROTATE_MASK) >> SPRITE_FLAG_ROTATE_BASE;
	int w, h;
	if( rotation & 1 )
	{
		// Rotated 90 or 270 degrees means that width and height should be flipped
		w = image->h;
		h = image->w;
	} else
	{
		w = image->w;
		h = image->h;
	}
	
	boundsLeft = x;
	boundsTop = y;
	boundsRight = x+w;
	boundsBottom = y+h;
}

void Sprite::SetFlippedX( bool _flipped )
{
	if( _flipped )
		SetFlags( SPRITE_FLAG_FLIP_X );
	else
		ClrFlags( SPRITE_FLAG_FLIP_X );
}

void Sprite::SetFlippedY( bool _flipped )
{
	if( _flipped )
		SetFlags( SPRITE_FLAG_FLIP_Y );
	else
		ClrFlags( SPRITE_FLAG_FLIP_Y );
}

int Sprite::GetOffset( int _x, int _y )
{
	int ret = 0;
	int rotation = (flags & SPRITE_FLAG_ROTATE_MASK) >> SPRITE_FLAG_ROTATE_BASE;
	switch( rotation )
	{
		case 0:
			ret = (_y*image->w)+_x;
			break;
			
		case 1:
			ret = ((image->w-1-_x)*image->h)+_y;
			break;
			
		case 2:
			ret = ((image->h-1-_y)*image->w)+(image->w-1-_x);
			break;
			
		case 3:
			ret = (_x*image->h)+(image->h-1-_y);
			break;
	}

	//printf( "Sprite GetOffset. Rotation=%i, x=%i, y=%i, offset=%i\n", rotation, _x, _y, ret );
	return ret;
}
