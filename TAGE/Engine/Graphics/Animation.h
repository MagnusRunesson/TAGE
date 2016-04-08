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
	int NumLoops;
	bool Loop;
	const AnimationFrameDefinition* Frames;
	const char* DEBUG_name;
};

class Animation
{
public:
	GameObject* pTarget;
	const AnimationSequenceDefinition* pSequence;
	bool IsPlaying;
	int FrameIndex;
	int FrameTime;
	int LoopCount;
	void (*pfnDoneCallback)();

	void Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget );
	void SetSequence( const AnimationSequenceDefinition* _pSequence );
	void SetDoneCallback( void(*_pfnDoneCallback)());
	void SetLoopCount( int _numLoops );
	void Update();
	void Reset();
	void Play();
	void Stop();
	void RefreshFrame();
};

#define DEFINE_ANIMATION( _name, _looping ) \
const AnimationSequenceDefinition animation_##_name = \
{ \
	sizeof( animation_##_name##_frames ) / sizeof( AnimationFrameDefinition ), \
	-1, \
	_looping, \
	animation_##_name##_frames, \
	#_name \
}

#define DEFINE_ANIMATION_LOOPFRAMES( _name, _looping, _numLoopFrames ) \
const AnimationSequenceDefinition animation_##_name = \
{ \
	sizeof( animation_##_name##_frames ) / sizeof( AnimationFrameDefinition ), \
	_numLoopFrames, \
	_looping, \
	animation_##_name##_frames \
}



#endif /* defined(__TinyShooter__ImageAnimation__) */
