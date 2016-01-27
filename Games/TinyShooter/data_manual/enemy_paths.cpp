//
//  enemy_paths.cpp
//  TinyShooter
//
//  Created by Magnus Runesson on 26/01/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include "data_manual/enemy_paths.h"

const PathPoint pathpoints_straight_right_to_left[] =
{
	{
		96,0,
	},
	{
		-16,0,
	}
};

const Path path_straight_right_to_left =
{
	2,
	pathpoints_straight_right_to_left,
};
