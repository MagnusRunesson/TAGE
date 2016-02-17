//
//  animation_explosion_big.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 24/01/16.
//  Copyright (c) 2016 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Graphics/Animation.h"
#include "data/alldata.h"

#define AEM_HOTSPOT_X (5)
#define AEM_HOTSPOT_Y (5)

const AnimationFrameDefinition animation_explosion_medium_frames[] =
{
	{
		&sprite_explosion_medium_00,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_01,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_02,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_03,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_04,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_05,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_06,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_07,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
	{
		&sprite_explosion_medium_08,
		5,
		0,
		AEM_HOTSPOT_X,
		AEM_HOTSPOT_Y,
	},
};

DEFINE_ANIMATION( explosion_medium, false );
