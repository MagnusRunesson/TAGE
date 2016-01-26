//
//  Image.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include "Engine/Types.h"

class Image
{
public:
	uint16 w;
	uint16 h;
	const uint16* pixels;
	const uint8* alpha;
	const uint8* DEBUG_name;
};

#endif /* Image_hpp */
