//
//  AudioHandler.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Audio/AudioMixer.h"
#include "Engine/Types.h"

#ifdef TAGE_TARGET_MACOSX

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

#else

#ifdef __cplusplus
extern "C" {
#endif

void Audio_Handler (void)
{
	audioMixer.outputReadPosition++;
	if( audioMixer.outputReadPosition >= audioMixer.outputBufferSize )
		audioMixer.outputReadPosition = 0;
	
	while( DAC->STATUS.bit.SYNCBUSY == 1 );
	DAC->DATA.reg = 127 + audioMixer.pOutputBuffer[ audioMixer.outputReadPosition ];
	while( DAC->STATUS.bit.SYNCBUSY == 1 );
	
	// Clear the interrupt
	TC5->COUNT16.INTFLAG.bit.MC0 = 1;
}

void TC5_Handler (void) __attribute__ ((weak, alias("Audio_Handler")));

#ifdef __cplusplus
}
#endif

#endif
