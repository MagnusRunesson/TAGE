//
//  AudioHandler.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "AudioHandler.h"
#include "types.h"


extern "C" const unsigned char sfx_pew_s8b_pcm_11025hz[];

void Audio_Handler_SDL( void *udata, uint8 *stream, int len )
{
	signed char* data = (signed char*)stream;
	
	int i;
	for( i=0; i<len; i++ )
	{
		if( i < 1320 )
			data[ i ] = sfx_pew_s8b_pcm_11025hz[ i ];
		else
			data[ i ] = 0;
		/*
		 signed char d = i;
		 d /= 8;
		 
		 data[ i ] = d;
		 */
	}
}
