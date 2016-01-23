//
//  sfx_player_fire_canon.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "sfx_player_fire_canon.h"
#include "AudioData.h"

extern "C" const sint8 audiosamples_pew_s8b_pcm_11025hz[];

extern "C" const AudioData sfx_player_fire_canon;

const AudioData sfx_player_fire_canon =
{
	1320,
	false,
	audiosamples_pew_s8b_pcm_11025hz,
};
