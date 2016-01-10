//
//  fp2d.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef fp2d_hpp
#define fp2d_hpp

#include "FixedPoint.h"

class fp2d
{
public:
	fp2d();
	fp2d( const fp2d& _o );
	fp2d( const FixedPoint& _x, const FixedPoint& _y );

	void operator -= ( const fp2d& _o );
	void operator += ( const fp2d& _o );
	void operator *= ( const FixedPoint& _o );

	fp2d operator - (const fp2d& _o );
	
	FixedPoint x;
	FixedPoint y;
};

#endif /* fp2d_hpp */
