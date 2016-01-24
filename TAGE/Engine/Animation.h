//
//  ImageAnimation.h
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#ifndef __TinyShooter__ImageAnimation__
#define __TinyShooter__ImageAnimation__

#include "types.h"

class GameObject;
class Image;

class AnimationFrameDefinition
{
public:
	const Image* sourceImage;
	uint8 Duration;
	uint8 Flags;
	sint8 HotspotX;
	sint8 HotspotY;
};

class AnimationSequenceDefinition
{
public:
	int NumFrames;
	const AnimationFrameDefinition* Frames;
};

class Animation
{
public:
	GameObject* pTarget;
	const AnimationSequenceDefinition* pSequence;
	int FrameIndex;
	int FrameTime;

	void Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget );
	void Update();
};


#endif /* defined(__TinyShooter__ImageAnimation__) */
