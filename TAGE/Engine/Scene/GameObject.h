//
//  GameObject.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-03.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Engine/Graphics/SpriteRenderer.h"
#include "Engine/Graphics/Animation.h"

class Image;
class Animation;
class AnimationSequenceDefinition;

class GameObject
{
	//
	//
	//
public:
	GameObject();
	void Reboot();
	void Create( const Image* _image );
	void Create( const AnimationSequenceDefinition* _animation );
	void Destroy();
	
	void Update();
	void Render();

	void SetHotspot( int _x, int _y );
	
	void SetWorldPosition( int _x, int _y );
	int GetWorldPositionX();
	int GetWorldPositionY();
	
	bool IsUsed();
	Sprite* GetSprite();
	const AnimationSequenceDefinition* GetAnimationSequenceDefinition();
	Animation* GetAnimation();

	void* m_customObject;
	void(*m_customUpdate)(void*);
	void(*m_customPreRender)(void*);
	void(*m_customPostRender)(void*);
	
	int m_flags;
	
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
	Animation m_animation;
	const AnimationSequenceDefinition* m_animationSequenceDefinition;
	
	//
	bool m_drawAlpha;
};

#endif /* GameObject_hpp */
