//
//  FixedPoint.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 30/11/15.
//  Copyright (c) 2015 Magnus Runesson. All rights reserved.
//

#include "Engine/Math/FixedPoint.h"

#define FRACTION_BITS (16)
#define FRACTION_BITS_HALF (FRACTION_BITS/2)
#define FRACTION_VALUES (1<<FRACTION_BITS)
#define FRACTION_VALUES_HALF (FRACTION_VALUES>>1)
#define FRACTION_MASK (FRACTION_VALUES-1)
#define INTEGER_BITS (15)
#define INTEGER_MASK (0xffff0000)

FixedPoint::FixedPoint()
{
	m_value = 0;
}

FixedPoint::FixedPoint( int _int )
{
	m_value = _int*FRACTION_VALUES;
}

FixedPoint::FixedPoint( int _int, int _fractionPercentage )
{
	int fraction = (_fractionPercentage * FRACTION_VALUES) / 100;
	m_value = (_int * FRACTION_VALUES) + fraction;
}

void FixedPoint::operator = (int o)
{
	m_value = o * FRACTION_VALUES;
}

void FixedPoint::operator = (FixedPoint o)
{
	m_value = o.m_value;
}

void FixedPoint::operator += (int o)
{
	m_value += o * FRACTION_VALUES;
}

void FixedPoint::operator += (FixedPoint o)
{
	m_value += o.m_value;
}

void FixedPoint::operator -= (int o)
{
	m_value -= o * FRACTION_VALUES;
}

void FixedPoint::operator -= (FixedPoint o)
{
	m_value -= o.m_value;
}

bool FixedPoint::operator < (int o)
{
	return m_value < (o*FRACTION_VALUES);
}

bool FixedPoint::operator < (FixedPoint o)
{
	return m_value < o.m_value;
}
	
bool FixedPoint::operator > (int o)
{
	return m_value > (o*FRACTION_VALUES);
}

bool FixedPoint::operator > (FixedPoint o)
{
	return m_value > o.m_value;
}

bool FixedPoint::operator <= (int o)
{
	return m_value <= (o*FRACTION_VALUES);
}

bool FixedPoint::operator <= (FixedPoint o)
{
	return m_value <= o.m_value;
}

bool FixedPoint::operator >= (int o)
{
	return m_value >= (o*FRACTION_VALUES);
}

bool FixedPoint::operator >= (FixedPoint o)
{
	return m_value >= o.m_value;
}

void FixedPoint::operator *= (int o)
{
	m_value *= o;
}

void FixedPoint::operator *= (FixedPoint o)
{
	m_value = (m_value>>FRACTION_BITS_HALF) * (o.m_value>>FRACTION_BITS_HALF);
}

void FixedPoint::operator /= (int o)
{
	m_value /= o;
}

void FixedPoint::operator /= (FixedPoint o)
{
	m_value = (m_value<<FRACTION_BITS_HALF) / (o.m_value<<FRACTION_BITS_HALF);
}

int FixedPoint::GetInteger()
{
	return m_value / FRACTION_VALUES;
}
