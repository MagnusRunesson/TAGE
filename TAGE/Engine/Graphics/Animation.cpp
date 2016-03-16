//
//  ImageAnimation.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Scene/GameObject.h"
#include "Engine/Graphics/Animation.h"

void Animation::Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget )
{
	pTarget = _pTarget;
	pSequence = _pSequence;
	FrameIndex = 0;
	FrameTime = 0;
	IsPlaying = false;
}

void Animation::SetSequence( const AnimationSequenceDefinition* _pSequence )
{
	pSequence = _pSequence;
	Reset();
}

void Animation::Reset()
{
	FrameIndex = 0;
	FrameTime = 0;
	LoopCount = pSequence->NumLoops;
	RefreshFrame();
}

void Animation::Play()
{
	IsPlaying = true;
	const AnimationFrameDefinition* pFrame = &pSequence->Frames[ FrameIndex ];
	pTarget->GetSprite()->image = pFrame->sourceImage;
	pTarget->SetHotspot( pFrame->HotspotX, pFrame->HotspotY );
}

void Animation::Stop()
{
	IsPlaying = false;
}

void Animation::RefreshFrame()
{
	const AnimationFrameDefinition* pFrame = &pSequence->Frames[ FrameIndex ];
	pTarget->GetSprite()->image = pFrame->sourceImage;
	pTarget->SetHotspot( pFrame->HotspotX, pFrame->HotspotY );
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
					if( LoopCount > 0 )
					{
						LoopCount--;
						if( LoopCount == 0 )
						{
							IsPlaying = false;
						} else
						{
							// Loop the loop
							FrameIndex -= pSequence->NumFrames;
						}
					}
				} else
				{
					IsPlaying = false;
				}
			}
			
			if( IsPlaying )
			{
				FrameTime -= duration;
				RefreshFrame();
			}
		}
	}
}
