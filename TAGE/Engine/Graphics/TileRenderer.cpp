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

void TileRenderer::ReadTile()
{
	m_tileMapIndex = (m_tileY * m_pTileMap->Width) + m_tileX;
	m_tile = m_pTileMap->Tiles[ m_tileMapIndex ];

	// Cache tile rendering flags
	m_flipX =(m_tile&0x8000) == 0x8000;
	m_flipY =(m_tile&0x4000) == 0x4000;
	m_flipD = (m_tile&0x2000) == 0x2000;
	
	// Discard all flag data to get the tile index
	m_tile &= 0x1fff;
	
	// Where to read the pixel data for this tile from
	m_tilePixelReadOfs = m_tile * m_pTileBank->TileHeight * m_pTileBank->TileWidth;
}

//
// Rendering
//
void TileRenderer::FrameStart()
{
	/*
	m_tileY = m_y / m_pTileBank->TileHeight;
	m_pixelY = m_y % m_pTileBank->TileHeight;
	m_tileX = m_x / m_pTileBank->TileWidth;
	m_pixelX = m_x % m_pTileBank->TileWidth;
	 */
	m_tileY = m_y >> 2;
	m_pixelY = m_y & 3;
	m_tileX = m_x >> 2;
	m_pixelX = m_x & 3;
	ReadTile();
}

void TileRenderer::NextPixel()
{
	m_pixelX++;
	if( m_pixelX >= m_pTileBank->TileWidth )
	{
		// New tile, woop!
		m_pixelX = 0;
		m_tileX++;
		ReadTile();
	}
}

void TileRenderer::NextScanline( bool _debugPrint )
{
	m_pixelY++;
	int tileHeight = m_pTileBank->TileHeight;
	if( m_pixelY >= tileHeight )
	{
		m_tileY++;
		m_pixelY -= tileHeight;
	}

	//m_tileX = m_x / m_pTileBank->TileWidth;
	//m_pixelX = m_x % m_pTileBank->TileWidth;
	m_tileX = m_x >> 2;
	m_pixelX = m_x & 0x3;
	ReadTile();
}

bool TileRenderer::RenderPixel( uint16* _pOutPixel )
{
	// Don't render tile with index 0, for perf
	if( m_tile == 0 )
	{
		NextPixel();
		return false;
	}

	int pixelY = m_pixelY;
	int pixelX = m_pixelX;
	if( m_flipX ) pixelX = m_pTileBank->TileWidth - pixelX - 1;
	if( m_flipY ) pixelY = m_pTileBank->TileHeight - pixelY - 1;
	if( m_flipD )
	{
		int t = pixelX;
		pixelX = pixelY;
		pixelY = t;
	}
	
	int tileReadOfs = m_tilePixelReadOfs + (pixelY*m_pTileBank->TileWidth) + pixelX;
	
	if( m_pTileBank->Alpha != NULL )
	{
		uint8 a = m_pTileBank->Alpha[ tileReadOfs ];
		if(	a == 0 )
			return false;
	}
	
	uint16 rgb = m_pTileBank->Pixels[ tileReadOfs ];
	*_pOutPixel = rgb;

	NextPixel();
	
	return true;
}

void TileRenderer::RenderScanline( uint16* _targetBuffer )
{
	uint16 rgb;
	int x;
	for( x=0; x<SCREEN_WIDTH; x++ )
	{
		if( RenderPixel( &rgb ))
			_targetBuffer[ x ] = rgb;
	}
}
