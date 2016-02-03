//
//  FixedPoint.h
//  TinyArcade
//
//  Created by Magnus Runesson on 30/11/15.
//  Copyright (c) 2015 Magnus Runesson. All rights reserved.
//

#ifndef __TinyArcade__FixedPoint__
#define __TinyArcade__FixedPoint__

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
	
	// Addition
	void operator += (int o);
	void operator += (FixedPoint o);
	FixedPoint operator + (int _o ) const;
	FixedPoint operator + (FixedPoint _o ) const;
	
	// Subtraction
	void operator -= (int o);
	void operator -= (FixedPoint o);
	FixedPoint operator - (int _o ) const;
	FixedPoint operator - (FixedPoint _o ) const;
	
	// Compare
	bool operator < (int o);
	bool operator < (FixedPoint o);
	bool operator > (int o);
	bool operator > (FixedPoint o);
	bool operator <= (int o);
	bool operator <= (FixedPoint o);
	bool operator >= (int o);
	bool operator >= (FixedPoint o);
	
	// Multiplication
	void operator *= (int o);
	void operator *= (FixedPoint o);
	FixedPoint operator * (int _o ) const;
	FixedPoint operator * (FixedPoint _o ) const;

	// Division
	void operator /= (int o);
	void operator /= (FixedPoint o);
	FixedPoint operator / (int o) const;
	FixedPoint operator / (FixedPoint o) const;
	
	int GetInteger();
	void SetRawValue( int _raw );
	
	//
	inline int GetDebugRawValue(){ return m_value; };
};

#endif /* defined(__TinyArcade__FixedPoint__) */
