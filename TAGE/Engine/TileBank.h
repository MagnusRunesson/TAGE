//
//  TileBank.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-27.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef TileBank_hpp
#define TileBank_hpp

#include "Types.h"

class CTileBank
{
public:
	uint8 TileWidth;
	uint8 TileHeight;
	uint16 NumTiles;
	
	uint16* Pixels;
	uint8* Alpha;
	
	uint8* DEBUG_Name;
};

#endif /* TileBank_hpp */
