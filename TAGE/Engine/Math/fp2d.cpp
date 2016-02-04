//
//  fp2d.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <math.h>
#include "Engine/Math/fp2d.h"
#include "Engine/Math/fpmath.h"

fp2d::fp2d()
{
	
}

fp2d::fp2d( const fp2d& _o )
{
	x = _o.x;
	y = _o.y;
}

fp2d::fp2d( const FixedPoint& _x, const FixedPoint& _y )
{
	x = _x;
	y = _y;
}

void fp2d::operator -= ( const fp2d& _o )
{
	x -= _o.x;
	y -= _o.y;
}

void fp2d::operator += ( const fp2d& _o )
{
	x += _o.x;
	y += _o.y;
}

void fp2d::operator *= ( const FixedPoint& _o )
{
	x *=_o;
	y *=_o;
}

fp2d fp2d::operator + (const fp2d& _o ) const
{
	fp2d ret = *this;
	ret += _o;
	return ret;
}

fp2d fp2d::operator - (const fp2d& _o ) const
{
	fp2d ret = *this;
	ret -= _o;
	return ret;
}

fp2d fp2d::operator * (const FixedPoint& _o ) const
{
	fp2d ret;
	ret.x = x * _o;
	ret.y = y * _o;
	return ret;
}

void fp2d::Normalize()
{
	FixedPoint fpl = (x*x)+(y*y);
	int sqrt = fisqrt( fpl.GetDebugRawValue() << 8 );
	fpl.SetRawValue( sqrt );
	//fpl.SetRawValue( l );
	x /= fpl;
	y /= fpl;
}

FixedPoint fp2d::Length() const
{
	FixedPoint ret;
	int nx = x.GetDebugRawValue();
	int ny = y.GetDebugRawValue();
	int l = (nx*nx)+(ny*ny);
	ret.SetRawValue( fisqrt( l << 8 ));
	return ret;
}
