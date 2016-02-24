//
//  AudioMixer.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef AudioMixer_h
#define AudioMixer_h

#include "Engine/Types.h"

class AudioSource;
class AudioStream;

class AudioMixer
{
public:
	uint32 outputBufferSize;
	sint8* pOutputBuffer;

	uint8 numChannels;
	AudioSource* channel;
	
	sint16 outputReadPosition;		// Where the hardware audio handler last read
	sint16 outputWritePosition;		// Where the audio mixer last wrote
	
	/*
	 
	 So the mixer will start by filling up the output buffer based on what's playing in the channels, then the audio handler will read from the buffer.
	 
	 That will happen in these steps:
	 1. The audio handler will read data from the output buffer
	 2. The mixer will identify that data have been read and replace the read samples with new samples
	 3. Repeat
	 
	 When we start the audio mixer the read and write position will be the same
	 After the audio handler have read some data from the mixer the read position will be greater than the write position
	 When we call AudioMixer::Update() it will identify that the write position is lagging behind the read position, thus identifying that there are samples in the output buffer that can be replaced
	 AudioMixer::Update() will write to the output buffer up until the position where it was last known to have been read
	 When that is done the write position will have caught up with the read position (Except not really, because when we've been filling up the audio buffer more samples will have been read from the output buffer. But the mixer will only read the length for filling up once, to avoid strange race conditions)
	
	 */
	AudioMixer( int _numChannels, AudioSource* _pChannels, uint32 _outputBufferSize, sint8* _pOutputBuffer );
	void Reboot();
	void Update();
	void SetFrequency( int _frequency );
	
	AudioSource* GetChannel( int _channel );
	AudioStream* GetStream( int _stream );
};

extern AudioMixer audioMixer;

#endif /* AudioMixer_h */
