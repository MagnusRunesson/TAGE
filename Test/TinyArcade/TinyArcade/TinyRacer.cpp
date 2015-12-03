//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <memory.h>
#include "TinyRacer.h"
#include "Screen.h"
#include "alldata.h"
#include "types.h"
#include "FixedPoint.h"
#include "Joypad.h"

FixedPoint fpX;
FixedPoint fpY;
FixedPoint fpSpeed;

void setup()
{
	fpSpeed = FixedPoint( 0, 25 );
	fpX = 10;
	fpY = 10;
}

void loop()
{
	int w = 5;
	int h = 5;
	int mx = SCREEN_WIDTH - w;
	int my = SCREEN_HEIGHT - h;
	sint8 padX, padY;
	uint16 keys = getPad( &padX, &padY );
	
	FixedPoint spx = padX;
	spx *= fpSpeed;
	FixedPoint spy = padY;
	spy *= fpSpeed;
	
	fpX += spx;
	fpY += spy;
	
	if( fpX < -10 )	fpX = -10;
	if( fpX > mx )	fpX = mx;
	if( fpY < -10 )	fpY = -10;
	if( fpY > my )	fpY = my;
	
	scbg.Draw( 0, 0 );
	
	int x = fpX.GetInteger();
	int y = fpY.GetInteger();
	test3.Draw( x, y );
}
