//
//  FixedPoint.cpp
//  TinyArcade
//
//  Created by Magnus Runesson on 30/11/15.
//  Copyright (c) 2015 Magnus Runesson. All rights reserved.
//

#include "FixedPoint.h"

#define MANTISSA_BITS (16)
#define MANTISSA_VALUES (1<<MANTISSA_BITS)
#define MANTISSA_MASK (0x8000ffff)
#define INTEGER_BITS (15)
#define INTEGER_MASK (0xffff0000)

FixedPoint::FixedPoint()
{
	m_value = 0;
}

FixedPoint::FixedPoint( int _int )
{
	m_value = _int*MANTISSA_VALUES;
}

FixedPoint::FixedPoint( int _int, int _mantissaPercentage )
{
	int mantissa = (_mantissaPercentage * MANTISSA_VALUES) / 100;
	m_value = (_int * MANTISSA_VALUES) + mantissa;
}

void FixedPoint::operator = (int o)
{
	m_value = o * MANTISSA_VALUES;
}

void FixedPoint::operator = (FixedPoint o)
{
	m_value = o.m_value;
}

void FixedPoint::operator += (int o)
{
	m_value += o * MANTISSA_VALUES;
}

void FixedPoint::operator += (FixedPoint o)
{
	m_value += o.m_value;
}

int FixedPoint::GetInteger()
{
	return m_value / MANTISSA_VALUES;
}

bool FixedPoint::operator < (int o)
{
	return m_value < (o*MANTISSA_VALUES);
}

bool FixedPoint::operator < (FixedPoint o)
{
	return m_value < o.m_value;
}
	
bool FixedPoint::operator > (int o)
{
	return m_value > (o*MANTISSA_VALUES);
}

bool FixedPoint::operator > (FixedPoint o)
{
	return m_value > o.m_value;
}

void FixedPoint::operator *= (int o)
{
	m_value *= (o*MANTISSA_VALUES);
}

void FixedPoint::operator *= (FixedPoint o)
{
	m_value *= o.m_value;
}
