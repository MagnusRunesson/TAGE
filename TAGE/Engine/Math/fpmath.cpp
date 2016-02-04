//
//  fpmath.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-04.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
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

FixedPoint SqrDistance( fp2d& _a, fp2d& _b )
{
	FixedPoint x = _b.x - _a.x;
	FixedPoint y = _b.y - _a.y;
	FixedPoint ret = (x*x)+(y*y);
	return ret;
}

const int ftbl[33]={0,1,1,2,2,4,5,8,11,16,22,32,45,64,90,128,181,256,362,512,724,1024,1448,2048,2896,4096,5792,8192,11585,16384,23170,32768,46340};
const int ftbl2[32]={ 32768,33276,33776,34269,34755,35235,35708,36174,36635,37090,37540,37984,38423,38858,39287,39712,40132,40548,40960,41367,41771,42170,42566,42959,43347,43733,44115,44493,44869,45241,45611,45977};

int fisqrt(int val)
{
	int cnt=0;
	int t=val;
	while (t) {cnt++;t>>=1;}
	if (6>=cnt)    t=(val<<(6-cnt));
	else           t=(val>>(cnt-6));
	
	return (ftbl[cnt]*ftbl2[t&31])>>15;
}

FixedPoint Distance(  fp2d& _a,  fp2d& _b )
{
	FixedPoint sqd = SqrDistance( _a, _b);
	sqd.SetRawValue( fisqrt( sqd.GetDebugRawValue() << 8 ));
	return sqd;
}
