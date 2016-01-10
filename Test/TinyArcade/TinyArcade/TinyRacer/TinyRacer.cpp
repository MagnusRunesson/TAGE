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
int worldWidth;
int worldHeight;

#define MAX( a, b ) ((a>b)?a:b)
#define MIN( a, b ) ((a<b)?a:b)

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

	worldWidth = testtrackmini.Width * tracktiles_mini.TileWidth;
	worldHeight = testtrackmini.Height * tracktiles_mini.TileHeight;
	
	background = new TileRenderer( &testtrackmini, &tracktiles_mini );
	
	// Set up game camera
	Camera::main = &mainCamera;

	// Setup player car
	playerCar.Create();
	playerCar.SetPosition( 25, 75 );
	
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
	if( camx > worldWidth-SCREEN_WIDTH ) camx = worldWidth-SCREEN_WIDTH;
	if( camy < 0 ) camy = 0;
	if( camy > worldHeight-SCREEN_HEIGHT ) camy = worldHeight-SCREEN_HEIGHT;
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
	uint16* mirrorScreen = screen;

	spriteRenderer.FrameStart();
	background->FrameStart();


	// Set this to the number of pixel rows in screen space that should be mirrored to enable the mirror effect
	int mirrorHeight = 0;
	
	/*
	 
	 Or use this code to use world space Y coordinate to enable the water effect
	 
	int worldMirrorStart = 230;		// Presto
	int mirrorHeight = (camy+SCREEN_HEIGHT) - worldMirrorStart;
	if( mirrorHeight < 0 )
		mirrorHeight = 0;
	 */
	
	int mirrorStart = SCREEN_HEIGHT-mirrorHeight;
	int copyStart = mirrorStart-mirrorHeight;
	
	int iScanline = 0;
	while( iScanline < mirrorStart )
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

		// Mirror test
		if( iScanline >= copyStart )
		{
			int destY = SCREEN_HEIGHT - (iScanline - copyStart);
			for( x=0; x<SCREEN_WIDTH; x++ )
			{
				uint16 rgb = lineBuffer[ x ];
				int r = (rgb >> 11);
				int g = (rgb >> 6) & 0x001f;
				int b = rgb & 0x001f;
				
				int i = (r+g+b)/3;
				int hi = i>>1;
				
				rgb = ((hi << 11) + (hi << 6) + i);
				mirrorScreen[ ((destY-1)*SCREEN_WIDTH) + x ] = rgb;
			}
		}

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
