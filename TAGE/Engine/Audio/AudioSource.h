//
//  AudioSource.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef AudioSource_h
#define AudioSource_h

#include "Engine/Types.h"
#include "Engine/Audio/AudioData.h"

class AudioSource
{
public:
	const AudioData* pAudioData;
	uint16 playbackPosition;
	bool isPlaying;
	
	void Reset();
	void SetData( const AudioData* _pData );
	void PlayFromBeginning();
	void Stop();
};

#endif /* AudioSource_h */
