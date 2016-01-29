//
//  fpmath.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-04.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef fpmath_hpp
#define fpmath_hpp

#include "Engine/Types.h"
#include "Engine/Math/FixedPoint.h"
#include "Engine/Math/fp2d.h"

sint16 fpsin( int _angle );
sint16 fpcos( int _angle );

FixedPoint SqrDistance( const fp2d& _a, const fp2d& _b );

#endif /* fpmath_hpp */
