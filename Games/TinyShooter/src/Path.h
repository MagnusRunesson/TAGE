//
//  Path.h
//  TinyShooter
//
//  Created by Magnus Runesson on 26/01/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef Path_h
#define Path_h

#include "Engine/types.h"

class PathPoint
{
public:
	sint16 x;
	sint16 y;
};

class Path
{
public:
	uint8 NumEntries;
	const PathPoint* Points;
};

#endif /* Path_h */
