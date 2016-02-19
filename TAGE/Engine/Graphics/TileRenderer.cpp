//
//  TileRenderer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Graphics/TileBank.h"
#include "Engine/Graphics/TileMap.h"
#include "Engine/Graphics/TileRenderer.h"
#include "Engine/Graphics/Screen.h"
#include "Engine/Debug.h"

TileRenderer::TileRenderer( const CTileMap* _pTileMap, const CTileBank* _tileBank )
{
	m_pTileBank = _tileBank;
	m_pTileMap = _pTileMap;
	m_x = 0;
	m_y = 0;
}

//
void TileRenderer::SetPosition( int _x, int _y )
{
	m_x = _x;
	m_y = _y;
}

//
void TileRenderer::GetPosition( int* _x, int* _y )
{
	*_x = m_x;
	*_y = m_y;
}

//
// Rendering
//
void TileRenderer::FrameStart()
{
	// NEW AND IMPROVED
	m_scanlineTixelY = m_y & 3;
	m_scanlineTixelX = m_x & 3;
	
	int tileX = m_x >> 2;
	int tileY = m_y >> 2;
	m_scanlineTileMapIndex = (tileY * m_pTileMap->Width) + tileX;
	
	PrepareScanlineRenderTiles();
}

// 000 - No flip flags at all
// 001 - Flip diagonally
// 010 - Flip Y
// 011 - Flip Y and flip diagonally
// 100 - Flip X
// 101 - Flip X and flip diagonally
// 110 - Flip X and flip Y
// 111 - Flip X, Y and diagonally

// Rotation in Tiled gives these flip flags
//   0° - 000
//  90° - 101
// 180° - 110
// 270° - 011

sint8 advX[ 8 ] = {
	1,		// 000 -      - No flip flags at all
	4,		// 001 -      - Flip diagonally
	1,		// 010 -      - Flip Y
	4,		// 011 - 270° - Flip Y and flip diagonally
	-1,		// 100 -      - Flip X
	-4,		// 101 -  90° - Flip X and flip diagonally
	-1,		// 110 - 180° - Flip X and flip Y
	-4,		// 111 -      - Flip X, Y and diagonally
};

sint8 advY[ 8 ] = {
	4,		// 000 -      - No flip flags at all
	1,		// 001 -      - Flip diagonally
	-4,		// 010 -      - Flip Y
	-1,		// 011 - 270° - Flip Y and flip diagonally
	4,		// 100 -      - Flip X
	1,		// 101 -  90° - Flip X and flip diagonally
	-4,		// 110 - 180° - Flip X and flip Y
	-1,		// 111 -      - Flip X, Y and diagonally
};

uint8 startOfs[ 8 ] = {
	0,		// 000 -      - No flip flags at all
	0,		// 001 -      - Flip diagonally
	12,		// 010 -      - Flip Y
	3,		// 011 - 270° - Flip Y and flip diagonally
	3,		// 100 -      - Flip X
	12,		// 101 -  90° - Flip X and flip diagonally
	15,		// 110 - 180° - Flip X and flip Y
	15,		// 111 -      - Flip X, Y and diagonally
};

void TileRenderer::PrepareScanlineRenderTiles( bool _debug )
{
	uint16* pTileData = &m_pTileMap->Tiles[ m_scanlineTileMapIndex ];

	int i;
	for( i=0; i<25; i++ )
	{
		// Read tile from tile map
		uint16 tile = *pTileData;
		pTileData++;

		// Fetch the render tile
		RenderTile* pTile = &m_renderTiles[ i ];

		if( _debug )
			debugLog( "Slot %2i - Tile: 0x%04x", i, tile );

		//
		int flipFlags = (tile&0xe000)>>13;
		pTile->TixelIncrementX = advX[ flipFlags ];
		pTile->TixelIncrementY = advY[ flipFlags ];
		pTile->StartTixelOffset = startOfs[ flipFlags ];
		pTile->TixelOffset = startOfs[ flipFlags ];

		if( _debug )
		{
			debugLog( " - FlipFlags: %c%c%c", ((flipFlags>>2)&1)?'1':'0', ((flipFlags>>1)&1)?'1':'0', ((flipFlags>>0)&1)?'1':'0' );
			debugLog( " - Start offset: %2i - TiX: %3i - TiY: %3i", pTile->TixelOffset, pTile->TixelIncrementX, pTile->TixelIncrementY );
		}

		// Discard all flag data to get the tile index
		tile &= 0x1fff;

		if( _debug )
			debugLog( " - TileIndex: %4i", tile );
		
		// Pre fetch the tixel data pointers for this tile
		int tileoffset = tile;
		tileoffset <<= 4;

		if( _debug )
			debugLog( " - Tile offset: %4i", tileoffset );

		pTile->pTileColor = &m_pTileBank->Pixels[ tileoffset ];
		if( tile == 0 )
			pTile->pTileColor = NULL;
		
		if( _debug )
			debugLog( " - Tile color pointer: 0x%08x", pTile->pTileColor );
		
		pTile->pTileAlpha = NULL;
		if( m_pTileBank->Alpha != NULL )
			pTile->pTileAlpha = &m_pTileBank->Alpha[ tileoffset ];
		
		if( _debug )
			debugLog( "\n" );
	}
}

void TileRenderer::AdvanceScanlineRenderTiles( int _newTixelY )
{
	int i;
	for( i=0; i<25; i++ )
	{
		// Fetch the render tile
		RenderTile* pTile = &m_renderTiles[ i ];
		pTile->TixelOffset = pTile->StartTixelOffset + (pTile->TixelIncrementY * _newTixelY);
	}
}

void TileRenderer::NextScanline( bool _debugPrint )
{
	m_scanlineTixelY++;
	if( m_scanlineTixelY >= 4 )
	{
		m_scanlineTixelY = 0;
		m_scanlineTileMapIndex += m_pTileMap->Width;
		PrepareScanlineRenderTiles();
	}
	else
	{
		AdvanceScanlineRenderTiles( m_scanlineTixelY );
	
	}
}

void TileRenderer::RenderScanline( uint16* _targetBuffer, uint8* _collisionBuffer )
{
	int writeX=0;
	int tx;
	
	//
	// Render the left most tile. It may be partially obscured
	//
	RenderTile* pTile = &m_renderTiles[ 0 ];
	if( pTile->pTileColor == NULL )
	{
		writeX += 4-m_scanlineTixelX;
	}
	else
	{
		for( tx=0; tx<4; tx++ )
		{
			uint16 rgb = pTile->pTileColor[ pTile->TixelOffset ];
			uint8 alpha = 255;
			if( pTile->pTileAlpha )
				alpha = pTile->pTileAlpha[ pTile->TixelOffset ];

			pTile->TixelOffset += pTile->TixelIncrementX;
			
			if(	tx < m_scanlineTixelX )
				continue;
		
			if( alpha == 255 )
			{
				// Full opacity, no blend
				_targetBuffer[ writeX ] = rgb;
				if( _collisionBuffer != NULL )
					_collisionBuffer[ writeX ] = 1;
				
			}

			writeX++;
		}
	}
	
	//
	int i;
	for( i=1; i<25; i++ )
	{
		// Fetch the render tile
		pTile = &m_renderTiles[ i ];
		if( pTile->pTileColor == NULL )
		{
			writeX += 4;
			if( writeX >= SCREEN_WIDTH )
				return;
			continue;
		}
		
		//
		for( tx=0; tx<4; tx++ )
		{
			uint16 rgb = pTile->pTileColor[ pTile->TixelOffset ];
			uint8 alpha = 255;
			if( pTile->pTileAlpha )
				alpha = pTile->pTileAlpha[ pTile->TixelOffset ];
			
			if( alpha == 255 )
			{
				// Full opacity, no blend
				_targetBuffer[ writeX ] = rgb;
				if( _collisionBuffer != NULL )
					_collisionBuffer[ writeX ] = 1;
				
			}
			
			pTile->TixelOffset += pTile->TixelIncrementX;
			writeX++;
			
			if( writeX >= SCREEN_WIDTH )
				return;
		}
	}
}
