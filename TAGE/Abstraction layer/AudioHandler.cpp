//
//  AudioHandler.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "types.h"
#include "AudioHandler.h"
#include "AudioMixer.h"


void Audio_Handler_SDL( void *udata, uint8 *stream, int len )
{
	signed char* data = (signed char*)stream;
	
	int i;
	for( i=0; i<len; i++ )
	{
		audioMixer.outputReadPosition++;
		if( audioMixer.outputReadPosition >= audioMixer.outputBufferSize )
			audioMixer.outputReadPosition = 0;
		
		data[ i ] = audioMixer.pOutputBuffer[ audioMixer.outputReadPosition ];
	}
}
