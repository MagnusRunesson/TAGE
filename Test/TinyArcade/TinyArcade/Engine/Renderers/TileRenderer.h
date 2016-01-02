//
//  TIleBankRenderer.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef TIleBankRenderer_hpp
#define TIleBankRenderer_hpp

#include "TileBank.h"

class TileRenderer
{
	int m_x;
	int m_y;
	CTileBank* m_pTileBank;
	
	int m_currentScanline;
	int m_tileY;
	int m_pixelY;
	
public:
	TileRenderer( CTileBank* _tileBank );
	
	//
	void SetPosition( int _x, int _y );

	//
	// Rendering
	//
	void FrameStart();
	void NextScanline( bool _debugPrint = false );
	void RenderScanline( uint16* _targetBuffer );
};

#endif /* TIleBankRenderer_hpp */
