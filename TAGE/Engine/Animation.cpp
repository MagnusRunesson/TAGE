//
//  ImageAnimation.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "GameObject.h"
#include "Animation.h"

void Animation::Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget )
{
	pTarget = _pTarget;
	pSequence = _pSequence;
	FrameIndex = 0;
	FrameTime = 0;
	IsPlaying = false;
}

void Animation::Reset()
{
	FrameIndex = 0;
	FrameTime = 0;
}

void Animation::Play()
{
	IsPlaying = true;
}

void Animation::Stop()
{
	IsPlaying = false;
}

void Animation::Update()
{
	if( IsPlaying )
	{
		FrameTime++;
		int duration = pSequence->Frames[ FrameIndex ].Duration;
		if( FrameTime >= duration )
		{
			FrameIndex++;
			if( FrameIndex >= pSequence->NumFrames )
			{
				// The end of the sequence. What now?
				if( pSequence->Loop )
				{
					// Loop the loop
					FrameIndex -= pSequence->NumFrames;
				} else
				{
					IsPlaying = false;
				}
			}
			
			if( IsPlaying )
			{
				FrameTime -= duration;
				pTarget->GetSprite()->image = pSequence->Frames[ FrameIndex ].sourceImage;
			}
		}
	}
}
