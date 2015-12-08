//
//  fpmath.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-04.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include "fpmath.h"
#include "Image.h"

#include "sinetable.h"


sint16 fpsin( int _angle )
{
	_angle &= 0xff;
	return sineTable[ _angle ];
}

sint16 fpcos( int _angle )
{
	return fpsin( _angle + 64 );
}