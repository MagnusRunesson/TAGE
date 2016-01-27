//
//  sfx_player_fire_canon.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "data_manual/sfx_player.h"
#include "Engine/Audio/AudioData.h"

extern "C" const unsigned char audiosamples_pew_s8b_pcm_11025hz[];
const AudioData sfx_player_fire_canon =
{
	1320,
	false,
	(const sint8*)audiosamples_pew_s8b_pcm_11025hz,
};


extern "C" const unsigned char audiosamples_pickup_s8b_pcm_11025[];
const AudioData sfx_player_pickup =
{
	8368,
	false,
	(const sint8*)audiosamples_pickup_s8b_pcm_11025,
};
