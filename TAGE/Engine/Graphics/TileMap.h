//
//  TileMap.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-03.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include "Engine/Types.h"

class CTileMap
{
public:
	uint8 Width;
	uint8 Height;
	uint16 Padda; // Padding for alignment. Not that it matters because it will be aligned automatically, but at least I remember that this is where to put additional data
	uint16* Tiles;
};

#endif /* TileMap_hpp */
