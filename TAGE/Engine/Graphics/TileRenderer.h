//
//  TileRenderer.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef TileRenderer_hpp
#define TileRenderer_hpp

#include "Engine/Types.h"

class CTileBank;
class CTileMap;

struct RenderTile
{
	const uint16* pTileColor;	// Pointer to the color data for this tile.
	const uint8* pTileAlpha;	// Pointer to the alpha data for this tile. Can be NULL.
	uint8 TixelOffset;		// Which tixel to read from
	uint8 StartTixelOffset;	// Which tixel to read from
	sint8 TixelIncrementX;	// For each X we move forward, how should we advance the reading offset. For regularly rendered tiles this should be 1, for flipped this should be -1, for rotated this can be .. well .. anything really :)
	sint8 TixelIncrementY;	// For each Y we move forward (scanline), how should we advance the reading offset. For regularly rendered tiles this should be 0, for flipped this should be -(tilewidth*2), for rotated tiles I don't really know now what it'll be.
};


class TileRenderer
{
	RenderTile m_renderTiles[ 25 ];	// This should really be (96/tilemapwidth)+1
	
	int m_x;
	int m_y;
	const CTileBank* m_pTileBank;
	const CTileMap* m_pTileMap;

	// Rendering variables
	int m_scanlineTileMapIndex;		// For each scanline this is the index in the tile map on the far left of the screen
	int m_scanlineTixelX;			// Which X position in the tile should we start at when we enter a new scanline
	int m_scanlineTixelY;			// Which Y position in the tile should we start at when we enter a new scanline
	int m_tilePixelReadOfs;
	
public:
	TileRenderer( const CTileMap* _tileMap, const CTileBank* _tileBank );
	
	//
	void SetPosition( int _x, int _y );
	void GetPosition( int* _x, int* _y );

	//
	// Rendering
	//
	void FrameStart();

	void PrepareScanlineRenderTiles( bool _debug = false );
	void AdvanceScanlineRenderTiles( int _newTixelY );

	void NextScanline( bool _debugPrint = false );
	void RenderScanline( uint16* _targetBuffer, uint8* _collisionBuffer );
};

#endif /* TileRenderer_hpp */
