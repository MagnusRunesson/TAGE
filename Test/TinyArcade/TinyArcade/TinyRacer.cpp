//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <memory.h>
#include "Screen.h"
#include "alldata.h"
#include "types.h"
#include "FixedPoint.h"
#include "Joypad.h"
#include "fpmath.h"

FixedPoint fpX;
FixedPoint fpY;
FixedPoint fpSpeed;
uint8 angle;

void setup()
{
	fpSpeed = FixedPoint( 0, 25 );
	fpX = 10;
	fpY = 10;
	angle = 0;
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
	
	//scbg.Draw( 0, 0 );
	testtrack.Draw( -20, 0 );
	
	//*
	if( fpX < -10 )	fpX = -10;
	if( fpX > SCREEN_WIDTH-10 )	fpX = SCREEN_WIDTH-10;
	if( fpY < -10 )	fpY = -10;
	if( fpY > SCREEN_HEIGHT-1 )	fpY = SCREEN_HEIGHT-1;
	int x = fpX.GetInteger();
	int y = fpY.GetInteger();
	carrot_3.DrawAlpha( x, y );
	/*/
	if( fpX < 0 )	fpX = 0;
	if( fpX > 240-SCREEN_WIDTH )	fpX = 240-SCREEN_WIDTH;
	if( fpY < 0 )	fpY = 0;
	if( fpY > 240-SCREEN_HEIGHT )	fpY = 240-SCREEN_HEIGHT;
	int x = fpX.GetInteger();
	int y = fpY.GetInteger();
	testtrack.Draw( -x, -y );
	/**/
	//rotest.Draw( 64, 32 );
	angle++;
}
