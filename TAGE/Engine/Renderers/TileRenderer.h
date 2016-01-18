//
//  TileRenderer.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef TileRenderer_hpp
#define TileRenderer_hpp

#include "TileBank.h"
#include "TileMap.h"

class TileRenderer
{
	int m_x;
	int m_y;
	CTileBank* m_pTileBank;
	CTileMap* m_pTileMap;
	
	int m_currentScanline;
	int m_tileY;
	int m_pixelY;
	
public:
	TileRenderer( CTileMap* _tileMap, CTileBank* _tileBank );
	
	//
	void SetPosition( int _x, int _y );
	void GetPosition( int* _x, int* _y );

	//
	// Rendering
	//
	void FrameStart();
	void NextScanline( bool _debugPrint = false );
	bool RenderPixel( int _x, uint16* _pOutPixel );
	void RenderScanline( uint16* _targetBuffer );
};

#endif /* TileRenderer_hpp */
