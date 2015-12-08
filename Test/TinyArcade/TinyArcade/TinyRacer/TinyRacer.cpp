//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

// STDC
#include <memory.h>

// TinyArcade game engine
#include "Screen.h"
#include "alldata.h"
#include "types.h"
#include "FixedPoint.h"
#include "Joypad.h"
#include "fpmath.h"
#include "Camera.h"

// Project specifics
#include "TinyRaceCar.h"

//
FixedPoint fpX;
FixedPoint fpY;
FixedPoint fpSpeed;
int angle;
TinyRaceCar playerCar;
Camera mainCamera;

void drawCarGrid();

void setup()
{
	Camera::main = &mainCamera;
	
	fpSpeed = FixedPoint( 0, 25 );
	fpX = 10;
	fpY = 10;
	angle = 0;
}

void loop()
{
	int y;
	
	padUpdate();
	
	
	playerCar.Update();
	
	testtrack.Draw( -20, -80 );

	//drawCarGrid();
	
	if( fpX < -10 )	fpX = -10;
	if( fpX > SCREEN_WIDTH-10 )	fpX = SCREEN_WIDTH-10;
	if( fpY < -10 )	fpY = -10;
	if( fpY > SCREEN_HEIGHT-1 )	fpY = SCREEN_HEIGHT-1;
	int x = fpX.GetInteger();
	y = fpY.GetInteger();
	//mainCamera.SetWorldPosition( x, y );
	playerCar.SetWorldPosition( x, y );
	playerCar.Render();

	angle++;
}

void drawTestCars()
{
	//testcar.DrawRotated( 34, 32, 0x40, 0x0100 );
	//testcarbig.DrawRotatedAlpha( 52, 42, angle>>2, 0x0800 );
	//testcar.DrawRotated( 70, 32, 0xa0, 0x0100 );
}

void drawCarGrid()
{
	int y = 8;
	int a = 0x00;
	testcar.DrawRotatedAlpha( 16, y, a, 0x0100 );
	carrot_1.DrawRotatedAlpha( 32, y, a, 0x0100 );
	carrot_2.DrawRotatedAlpha( 48, y, a, 0x0100 );
	carrot_3.DrawRotatedAlpha( 64, y, a, 0x0100 );
	
	y = 22;
	a = 0x40;
	testcar.DrawRotatedAlpha( 16, y, a, 0x0100 );
	carrot_1.DrawRotatedAlpha( 32, y, a, 0x0100 );
	carrot_2.DrawRotatedAlpha( 48, y, a, 0x0100 );
	carrot_3.DrawRotatedAlpha( 64, y, a, 0x0100 );
	
	y = 36;
	a = 0x80;
	testcar.DrawRotatedAlpha( 16, y, a, 0x0100 );
	carrot_1.DrawRotatedAlpha( 32, y, a, 0x0100 );
	carrot_2.DrawRotatedAlpha( 48, y, a, 0x0100 );
	carrot_3.DrawRotatedAlpha( 64, y, a, 0x0100 );
	
	y = 50;
	a = 0xc0;
	testcar.DrawRotatedAlpha( 16, y, a, 0x0100 );
	carrot_1.DrawRotatedAlpha( 32, y, a, 0x0100 );
	carrot_2.DrawRotatedAlpha( 48, y, a, 0x0100 );
	carrot_3.DrawRotatedAlpha( 64, y, a, 0x0100 );
}
