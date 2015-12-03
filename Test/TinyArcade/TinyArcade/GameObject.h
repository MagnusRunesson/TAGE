//
//  GameObject.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "Image.h"

class GameObject
{
	Image* m_image;
	int m_x;
	int m_y;
	
public:
	GameObject( Image* _image );
	void Update();
	void Render();
};

#endif /* GameObject_hpp */
