//
//  TinyRacer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

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
TinyRaceCar playerCar;
GameObject coolbackground( &testtrack );
Camera mainCamera;

void drawCarGrid();

void setup()
{
	Camera::main = &mainCamera;
	
	playerCar.SetPosition( 10, 10 );
}

void loop()
{
	//
	// Update system stuff
	//
	padUpdate();
	
	//
	// Update game logic
	//
	
	// Player car
	playerCar.Update();

	// Camera should follow player car
	int camx = playerCar.GetWorldPositionX()-48;
	int camy = playerCar.GetWorldPositionY()-32;
	if( camx < 0 ) camx = 0;
	if( camx > 240-SCREEN_WIDTH ) camx = 240-SCREEN_WIDTH;
	if( camy < 0 ) camy = 0;
	if( camy > 240-SCREEN_HEIGHT ) camy = 240-SCREEN_HEIGHT;
	mainCamera.SetWorldPosition( camx, camy );
	
	//
	// Render
	//
	coolbackground.Render();
	playerCar.Render();
}
