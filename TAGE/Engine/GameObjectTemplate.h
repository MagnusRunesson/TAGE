//
//  GameObjectTemplate.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2016-01-03.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef GameObjectTemplate_hpp
#define GameObjectTemplate_hpp

#include "types.h"
#include "Image.h"

class CGameObjectTemplate
{
public:
	sint16 WorldPosX;
	sint16 WorldPosY;
	Image* Image;
};

#endif /* GameObjectTemplate_hpp */
