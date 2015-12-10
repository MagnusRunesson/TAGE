//
//  FixedPoint.h
//  TinyArcade
//
//  Created by Magnus Runesson on 30/11/15.
//  Copyright (c) 2015 Magnus Runesson. All rights reserved.
//

#ifndef __TinyArcade__FixedPoint__
#define __TinyArcade__FixedPoint__

#include <stdio.h>

class FixedPoint
{
protected:
	int m_value;
	
public:
	FixedPoint();
	FixedPoint( int _int );
	FixedPoint( int _int, int _fractionPercentage );
	void operator = (int o);
	void operator = (FixedPoint o);
	void operator += (int o);
	void operator += (FixedPoint o);
	void operator -= (int o);
	void operator -= (FixedPoint o);
	bool operator < (int o);
	bool operator < (FixedPoint o);
	bool operator > (int o);
	bool operator > (FixedPoint o);
	void operator *= (int o);
	void operator *= (FixedPoint o);
	void operator /= (int o);
	void operator /= (FixedPoint o);
	int GetInteger();
	
	//
	inline int GetDebugRawValue(){ return m_value; };
};

#endif /* defined(__TinyArcade__FixedPoint__) */
