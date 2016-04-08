//
//  ImageAnimation.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 20/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include <stdlib.h>
#include "Engine/Scene/GameObject.h"
#include "Engine/Graphics/Animation.h"

void Animation::Create( const AnimationSequenceDefinition* _pSequence, GameObject* _pTarget )
{
	pTarget = _pTarget;
	pSequence = _pSequence;
	FrameIndex = 0;
	FrameTime = 0;
	IsPlaying = false;
	pfnDoneCallback = NULL;
}

void Animation::SetSequence( const AnimationSequenceDefinition* _pSequence )
{
	pSequence = _pSequence;
	Reset();
}

void Animation::SetDoneCallback( void(*_pfnDoneCallback)())
{
	pfnDoneCallback = _pfnDoneCallback;
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
		bool callCallback = false;
		
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
					bool doLoop = true;
					
					if( LoopCount > 0 )
					{
						LoopCount--;
						if( LoopCount == 0 )
						{
							doLoop = false;
							callCallback = true;
							IsPlaying = false;
						}
					}
					
					if( doLoop )
					{
						// Loop the loop
						FrameIndex -= pSequence->NumFrames;
					}
				} else
				{
					callCallback = true;
					IsPlaying = false;
				}
			}
			
			if( IsPlaying )
			{
				FrameTime -= duration;
				RefreshFrame();
			}
		}
		
		if( callCallback && (pfnDoneCallback != NULL))
		   pfnDoneCallback();
	}
}
