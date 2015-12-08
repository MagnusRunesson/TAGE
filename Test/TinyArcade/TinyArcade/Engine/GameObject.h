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
	//
	//
	//
public:
	GameObject( Image* _image );
	virtual void Update();
	virtual void Render();

	void SetWorldPosition( int _x, int _y );
	
	//
	//
	//
protected:
	//
	int m_worldPositionX;
	int m_worldPositionY;
	
	//
	Image* m_image;
	int m_imageHotspotX;
	int m_imageHotspotY;
};

#endif /* GameObject_hpp */
