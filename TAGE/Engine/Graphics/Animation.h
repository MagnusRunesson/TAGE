//
//  ImageAnimation.h
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#ifndef __TinyShooter__ImageAnimation__
#define __TinyShooter__ImageAnimation__

#include "Engine/Types.h"

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
	bool Loop;
	const AnimationFrameDefinition* Frames;
};

class Animation
{
public:
	GameObject* pTarget;
	const AnimationSequenceDefinition* pSequence;
	bool IsPlaying;
	int FrameIndex;
	int FrameTime;

	void Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget );
	void SetSequence( const AnimationSequenceDefinition* _pSequence );
	void Update();
	void Reset();
	void Play();
	void Stop();
};


#endif /* defined(__TinyShooter__ImageAnimation__) */
