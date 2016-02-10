//
//  TileRenderer.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef TileRenderer_hpp
#define TileRenderer_hpp

class CTileBank;
class CTileMap;

class TileRenderer
{
	int m_x;
	int m_y;
	const CTileBank* m_pTileBank;
	const CTileMap* m_pTileMap;
	
	int m_currentScanline;
	int m_tileY;
	int m_pixelY;
	
	int m_tileX;
	int m_pixelX;
	int m_tileMapIndex;
	int m_tile;
	bool m_flipX;
	bool m_flipY;
	bool m_flipD;
	int m_tileReadOfs;
	
public:
	TileRenderer( const CTileMap* _tileMap, const CTileBank* _tileBank );
	
	//
	void SetPosition( int _x, int _y );
	void GetPosition( int* _x, int* _y );

	//
	// Rendering
	//
	void FrameStart();
	void NextScanline( bool _debugPrint = false );
	bool RenderPixel( uint16* _pOutPixel );
	void RenderScanline( uint16* _targetBuffer );
	
private:
	void ReadTile();
	void NextPixel();
};

#endif /* TileRenderer_hpp */
