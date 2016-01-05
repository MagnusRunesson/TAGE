//
//  TileRenderer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "TileRenderer.h"
#include "Screen.h"

TileRenderer::TileRenderer( CTileMap* _pTileMap, CTileBank* _tileBank )
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
	m_tileY = m_y / m_pTileBank->TileHeight;
	m_pixelY = m_y % m_pTileBank->TileHeight;
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
}

void TileRenderer::RenderScanline( uint16* _targetBuffer )
{
	
	int x;
	for( x=0; x<SCREEN_WIDTH; x++ )
	{
		int tileX = (m_x+x) / m_pTileBank->TileWidth;
		int pixelX = (m_x+x) % m_pTileBank->TileWidth;

		int tileMapIndex = (m_tileY * m_pTileMap->Width) + tileX;
		
		int iTile = m_pTileMap->Tiles[ tileMapIndex ];
		bool flipX =(iTile&0x8000) == 0x8000;
		bool flipY =(iTile&0x4000) == 0x4000;
		bool flipD = (iTile&0x2000) == 0x2000;
		iTile &= 0x1fff;

		int pixelY = m_pixelY;
		if( flipX ) pixelX = m_pTileBank->TileWidth - pixelX - 1;
		if( flipY ) pixelY = m_pTileBank->TileHeight - pixelY - 1;
		if( flipD )
		{
			int t = pixelX;
			pixelX = pixelY;
			pixelY = t;
		}
		
		int tileReadOfs = (iTile * m_pTileBank->TileWidth * m_pTileBank->TileHeight) + (pixelY*m_pTileBank->TileWidth) + pixelX;
		uint16 rgb = m_pTileBank->Pixels[ tileReadOfs ];
		_targetBuffer[ x ] = rgb;
	}
}
