//
//  TileRenderer.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "TileRenderer.h"
#include "Screen.h"

TileRenderer::TileRenderer( CTileBank* _tileBank )
{
	m_pTileBank = _tileBank;
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
		
		int iTile = (m_tileY*12)+tileX;
		
		int tileReadOfs = (iTile * m_pTileBank->TileWidth * m_pTileBank->TileHeight) + (m_pixelY*m_pTileBank->TileWidth) + pixelX;
		uint16 rgb = m_pTileBank->Pixels[ tileReadOfs ];
		_targetBuffer[ x ] = rgb;
	}
}
