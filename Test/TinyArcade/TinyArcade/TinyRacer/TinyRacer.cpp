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
#include "GameObjectManager.h"
#include "TileRenderer.h"

// Project specifics
#include "TinyRaceCar.h"

//
TinyRaceCar playerCar;
GameObject* coolbackground;
Camera mainCamera;
TileRenderer* background;

bool debugSpriteRenderer;

void(*pfnHBlankInterrupt)(int);

void HBlankInterrupt( int _scanline )
{
	/*
	if( _scanline < 5 )
	{
		int x, y;
		background->GetPosition( &x, &y );
		x--;
		background->SetPosition( x, y );
	} else if( _scanline > 59 )
	{
		int x, y;
		background->GetPosition( &x, &y );
		x++;
		background->SetPosition( x, y );
	}
	 */
	
	//printf( "Scanline=%i\n", _scanline );
}

void setup()
{
	// Create the sprite background
	//coolbackground = gameObjectManager.CreateGameObject( &testtrack );

	background = new TileRenderer( &testtrackmini, &tracktiles_mini );
	
	// Set up game camera
	Camera::main = &mainCamera;

	// Setup player car
	playerCar.Create();
	playerCar.SetPosition( 10, 10 );
	
	//
	// Debug triggers
	//
	debugSpriteRenderer = false;
	
	pfnHBlankInterrupt = HBlankInterrupt;
}

void loop()
{
	//
	// Update system stuff
	//
	padUpdate();
	
	//
	// Update all game objects
	//
	gameObjectManager.Update();

	//
	// Camera should follow player car
	//
	int camx = playerCar.GetWorldPositionX()-48;
	int camy = playerCar.GetWorldPositionY()-32;
	if( camx < 0 ) camx = 0;
	if( camx > 240-SCREEN_WIDTH ) camx = 240-SCREEN_WIDTH;
	if( camy < 0 ) camy = 0;
	if( camy > 240-SCREEN_HEIGHT ) camy = 240-SCREEN_HEIGHT;
	mainCamera.SetWorldPosition( camx, camy );
	background->SetPosition( camx, camy );
	
	//
	// Tell all game objects that it is time to be rendered
	//
	gameObjectManager.Render();
	
	
	//
	// Scanline rendered
	//
	unsigned short lineBuffer[ SCREEN_WIDTH ];
	uint16* screen = screenBuffer;

	spriteRenderer.FrameStart();
	background->FrameStart();

	int iScanline = 0;
	while( iScanline < SCREEN_HEIGHT-1 )
	{
		// Clear line buffer
		int x;
		for( x=0; x<SCREEN_WIDTH; x++ )
			lineBuffer[ x ] = 0;

		if( pfnHBlankInterrupt != NULL )
			pfnHBlankInterrupt( iScanline );
		
		// Render sprites to line buffer
		background->RenderScanline( lineBuffer );
		spriteRenderer.RenderScanline( lineBuffer );

		// Copy to screen
		for( x=0; x<SCREEN_WIDTH; x++ )
			*screen++ = lineBuffer[ x ];

		spriteRenderer.NextScanline( debugSpriteRenderer );
		background->NextScanline();
		
		iScanline++;
	}
	
	//
	// Reset debug triggers
	//
	debugSpriteRenderer = false;
}

void debugTrigger( int _trigger )
{
	if( _trigger == 0 )
	{
		debugSpriteRenderer = true;
	}
}
