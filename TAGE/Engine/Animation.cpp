//
//  ImageAnimation.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "GameObject.h"
#include "Animation.h"

void Animation::Create( AnimationSequenceDefinition* _pSequence, GameObject* _pTarget )
{
	pTarget = _pTarget;
	pSequence = _pSequence;
	FrameIndex = 0;
	FrameTime = 0;
}

void Animation::Update()
{
	FrameTime++;
	int duration = pSequence->Frames[ FrameIndex ].Duration;
	if( FrameTime >= duration )
	{
		FrameIndex++;
		if( FrameIndex >= pSequence->NumFrames )
			FrameIndex -= pSequence->NumFrames;
		FrameTime -= duration;
		
		pTarget->GetSprite()->image = pSequence->Frames[ FrameIndex ].sourceImage;
	}
}
