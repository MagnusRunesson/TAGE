//
//  AudioStream.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-02-24.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "AudioStream.h"

#ifndef TAGE_TARGET_MACOSX

#include <SdFat.h>

//
// Arduino
//

SdFat sd;
SdFile file;

#endif



#define SWAP_PAGE( _a ){ _a=(_a==0)?1:0; }



AudioStream::AudioStream()
{
	Reset();
}

void AudioStream::Reset()
{
	m_lastStreamBufferPage = 1;						// The page we streamed from last time we read file data
	m_currentStreamBufferPage = 0;					// The page we are currently streaming from
	m_currentStreamBufferIndex = 0;					// The byte offset in a page we are currently streaming from
	m_currentStreamBuffer = m_streamBufferA;		// Shortcut to the current page to stream from
	m_streamBuffers[ 0 ] = m_streamBufferA;
	m_streamBuffers[ 1 ] = m_streamBufferB;
	m_isPlaying = false;
}

void AudioStream::OpenStream( const char *_pszFileName )
{
	Reset();
	
#ifdef TAGE_TARGET_MACOSX
	
#else
	char buffe[ 100 ];

	snprintf( buffe, 99, "/Tiny Shooter/%s", _pszFileName );

	// Initialize SD lib
	sd.begin( 10, SPI_FULL_SPEED );
	
	// Open the file and read some stuffs
	file.open( buffe, O_READ );
	file.read( m_streamBufferA, STREAM_BUFFER_SIZE );
	file.read( m_streamBufferB, STREAM_BUFFER_SIZE );
	
#endif
}

void AudioStream::CloseStream()
{
	Pause();
}

void AudioStream::Play()
{
	m_isPlaying = true;
}

void AudioStream::Pause()
{
	m_isPlaying = false;
}

void AudioStream::Update()
{
#ifdef TAGE_TARGET_MACOSX
	
#else
	// Wait until we started streaming from the last page we read
	if( m_lastStreamBufferPage != m_currentStreamBufferPage )
		return;
	
	// At this point the audio playback have started streaming from the last read page, so we need to quickly load another page
	SWAP_PAGE( m_lastStreamBufferPage );
	
	// Figure out if we can read a whole page or need to read some data, rewind the file, and read the rest
	if( file.available() < STREAM_BUFFER_SIZE )
	{
		// Read the end part of the file
		int readAmount = file.available();
		file.read( m_streamBuffers[ m_lastStreamBufferPage ], readAmount );
		
		// Rewind to the beginning of the file
		file.rewind();
		
		// Fill the rest of the buffer from the beginning of the file
		int readLeft = STREAM_BUFFER_SIZE - readAmount;
		file.read( m_streamBuffers[ m_lastStreamBufferPage ], readLeft );
	} else
	{
		// There is enough data left in the file, just read the whole page
		file.read( m_streamBuffers[ m_lastStreamBufferPage ], STREAM_BUFFER_SIZE );
	}
#endif
}

sint8 AudioStream::GetNextSample()
{
	sint8 ret = m_currentStreamBuffer[ m_currentStreamBufferIndex ];
	
	//
	m_currentStreamBufferIndex++;
	if( m_currentStreamBufferIndex >= STREAM_BUFFER_SIZE )
	{
		// Reset from the beginning
		m_currentStreamBufferIndex = 0;
		
		// Swap which buffer to play from
		SWAP_PAGE( m_currentStreamBufferPage );
		m_currentStreamBuffer = m_streamBuffers[ m_currentStreamBufferPage  ];
		
		// Load more data yo!
		Update();
	}
	
	return ret;
}
