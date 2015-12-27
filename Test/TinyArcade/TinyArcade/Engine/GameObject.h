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
#include "SpriteRenderer.h"

class GameObject
{
	//
	//
	//
public:
	GameObject();
	void Create( Image* _image );
	void Destroy();
	
	void Update();
	void Render();

	void SetHotspot( int _x, int _y );
	
	void SetWorldPosition( int _x, int _y );
	int GetWorldPositionX();
	int GetWorldPositionY();
	
	Sprite* GetSprite();

	void* m_customObject;
	void(*m_customUpdate)(void*);
	void(*m_customPreRender)(void*);
	void(*m_customPostRender)(void*);
	
	//
	//
	//
protected:
	//
	int m_worldPositionX;
	int m_worldPositionY;

	//
	//Image* m_image;
	Sprite* m_sprite;
	int m_imageHotspotX;
	int m_imageHotspotY;
	
	//
	bool m_drawAlpha;
};

#endif /* GameObject_hpp */
