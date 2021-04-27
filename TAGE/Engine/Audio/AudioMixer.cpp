//
//  AudioMixer.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Audio/AudioMixer.h"
#include "Engine/Audio/AudioSource.h"
#include "Engine/Audio/AudioData.h"
#include "Engine/Audio/AudioStream.h"

// This specify the number of input channels. In theory there can be as many input channels
// as you'd like, just make sure not too many are playing at the same time. For example, you
// might want to set up 1 channel for the player SFX, 2 channels for explosions, 2 channels
// for various enemy SFX etc, but as long as they are not all playing at the same time you
// should be just fine performance wise.
const int NUM_CHANNELS = 4;
const int NUM_STREAMS = 1;
AudioSource audioChannels[ NUM_CHANNELS ];
AudioStream audioStreams[ NUM_STREAMS ];

// The output buffer size is specified in bytes, but since the hardware output audio is 1 byte
// per channel, 1 channel we are specifying how many samples we should have in the buffer. We
// output at 11025Hz, so that means 11025 bytes per second. At 60 fps that means 11025/60≈184
// bytes per frame.
const int OUTPUT_BUFFER_SIZE = 1200;
sint8 audioMixOutputBuffer[ OUTPUT_BUFFER_SIZE ];

// Create the instance of the audio mixer
AudioMixer audioMixer( NUM_CHANNELS, audioChannels, OUTPUT_BUFFER_SIZE, audioMixOutputBuffer );

//
AudioMixer::AudioMixer( int _numChannels, AudioSource* _pChannels, uint32 _outputBufferSize, sint8* _pOutputBuffer )
{
	// Set up output buffer
	outputBufferSize = _outputBufferSize;
	pOutputBuffer = _pOutputBuffer;
	
	// Setup input channels
	numChannels = _numChannels;
	channel = _pChannels;
	
	// Clear the output buffer
	int i;
	for( i=0; i<outputBufferSize; i++ )
		pOutputBuffer[ i ] = 0;

	//
	outputReadPosition = 0;
	outputWritePosition = 0;
	
	//
	Reboot();
}

void AudioMixer::Reboot()
{
	// Clear the input channels
	int i;
	for( i=0; i<numChannels; i++ )
		channel[ i ].Reset();
	
}

void AudioMixer::Update()
{
	int bytesToFill = outputReadPosition-outputWritePosition;
	if( bytesToFill < 0 )
	{
		// Audio buffer have looped
		bytesToFill += outputBufferSize;
	}
	
	int i=0;
	while( i<bytesToFill )
	{
		int apa = 0;
		
		int iChannel;
		for( iChannel=0; iChannel<NUM_CHANNELS; iChannel++ )
		{
			AudioSource* chan = &channel[ iChannel ];
			const AudioData* data = chan->pAudioData;
			
			if( chan->isPlaying )
			{
				apa += data->samples[ chan->playbackPosition ];
				
				chan->playbackPosition++;
				if( chan->playbackPosition >= data->length )
				{
					if( data->looping )
					{
						chan->playbackPosition -= data->length;
					} else
					{
						chan->isPlaying = false;
					}
				}
			}
		}

		// Mix in the stream if it is playing
		AudioStream* pStream = &audioStreams[ 0 ];
		if( pStream->m_isPlaying )
			apa += pStream->GetNextSample();

		// Clip if needed
		if( apa > 127 ) apa = 127;
		if( apa < -127 ) apa = -127;

		// And done
		pOutputBuffer[ outputWritePosition ] = apa;
		
		//
		outputWritePosition++;
		if( outputWritePosition >= outputBufferSize )
			outputWritePosition -= outputBufferSize;
		
		//
		i++;
	}
}

#ifdef TAGE_TARGET_MACOSX

extern void audioInit( int _frequency );

#elif TAGE_TARGET_TINYARCADE

void tcConfigure( uint32 sampleRate );
void tcStart();
void tcStop();

#elif TAGE_TARGET_GW

extern void audioInit( int _frequency );

#endif

void AudioMixer::SetFrequency( int _frequency )
{
	outputBufferSize = _frequency >> 5;
	
#ifdef TAGE_TARGET_MACOSX
	audioInit( _frequency );
#elif TAGE_TARGET_TINYARCADE
	tcStop();
	tcConfigure( _frequency );
	tcStart();
#elif TAGE_TARGET_GW
#endif
}


AudioSource* AudioMixer::GetChannel( int _iChannel )
{
	return &channel[ _iChannel ];
}

AudioStream* AudioMixer::GetStream( int _stream )
{
	return &audioStreams[ _stream ];
}
