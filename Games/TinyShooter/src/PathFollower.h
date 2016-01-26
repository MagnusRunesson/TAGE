//
//  PathFollower.hpp
//  TinyShooter
//
//  Created by Magnus Runesson on 26/01/16.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef PathFollower_hpp
#define PathFollower_hpp

#include "types.h"
#include "Path.h"
#include "fp2d.h"

class PathFollower
{
	// Static data
	const Path* m_pPathData;
	FixedPoint m_speed;
	int m_offsetX;
	int m_offsetY;
	
	// Switch these as we go from node to node. The also
	fp2d m_currentFrom;
	fp2d m_currentTo;
	
	// This interpolates from one node to the next (m_currentFrom to m_currentTo)
	FixedPoint m_currentTime;
	
	//
	fp2d m_currentPosition;
	
public:
	PathFollower();
	
	void SetPath( const Path* _pPath, FixedPoint _speed, int _offsetX, int _offsetY );
	void Update();
	
	fp2d GetCurrentPosition();
};

#endif /* PathFollower_hpp */
