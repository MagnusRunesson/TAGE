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
const AudioData sfx_player_fire_pew =
{
	1289,
	false,
	(const sint8*)audiosamples_pew_s8b_pcm_11025hz,
};


extern "C" const unsigned char audiosamples_double_pew_s8b_pcm_11025hz[];
const AudioData sfx_player_fire_double_pew =
{
	1852,
	false,
	(const sint8*)audiosamples_double_pew_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_laser_s8b_pcm_11025hz[];
const AudioData sfx_player_fire_laser =
{
	10789,
	false,
	(const sint8*)audiosamples_laser_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_bomb_s8b_pcm_11025hz[];
const AudioData sfx_player_fire_bomb =
{
	4870,
	false,
	(const sint8*)audiosamples_bomb_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_pickup_s8b_pcm_11025hz[];
const AudioData sfx_player_pickup =
{
	7025,
	false,
	(const sint8*)audiosamples_pickup_s8b_pcm_11025hz,
};


extern "C" const unsigned char audiosamples_explosion_short_a_s8b_pcm_11025hz[];
const AudioData sfx_explosion_short_a =
{
	2647,
	false,
	(const sint8*)audiosamples_explosion_short_a_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_explosion_short_b_s8b_pcm_11025hz[];
const AudioData sfx_explosion_short_b =
{
	3086,
	false,
	(const sint8*)audiosamples_explosion_short_b_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_explosion_medium_a_s8b_pcm_11025hz[];
const AudioData sfx_explosion_medium_a =
{
	4973,
	false,
	(const sint8*)audiosamples_explosion_medium_a_s8b_pcm_11025hz
};


extern "C" const unsigned char audiosamples_music_boss_s8b_pcm_11025hz[];
const AudioData music_boss =
{
	35852,
	false,
	(const sint8*)audiosamples_music_boss_s8b_pcm_11025hz,
};

/*
extern "C" const unsigned char audiosamples_music_titlescreen_s8b_pcm_11025hz[];
const AudioData music_titlescreen =
{
	211476,
	true,
	(const sint8*)audiosamples_music_titlescreen_s8b_pcm_11025hz,
};
*/
