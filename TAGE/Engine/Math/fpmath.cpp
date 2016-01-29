//
//  fpmath.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-04.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Types.h"
#include "Engine/Math/fpmath.h"
#include "Engine/Math/sinetable.h"
#include "Engine/Math/FixedPoint.h"
#include "Engine/Math/fp2d.h"

sint16 fpsin( int _angle )
{
	_angle &= 0xff;
	return sineTable[ _angle ];
}

sint16 fpcos( int _angle )
{
	return fpsin( _angle + 64 );
}

FixedPoint SqrDistance( const fp2d& _a, const fp2d& _b )
{
	FixedPoint x = _b.x - _a.x;
	FixedPoint y = _b.y - _a.y;
	
	FixedPoint ret = (x*x)+(y*y);
	return ret;
}
