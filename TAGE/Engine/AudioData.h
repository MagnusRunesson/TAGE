//
//  AudioData.h
//  TinyShooter
//
//  Created by Magnus Runesson on 2016-01-23.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#ifndef AudioData_h
#define AudioData_h

#include "types.h"

class AudioData
{
public:
	uint32 length;
	sint8 samples[];
};

#endif /* AudioData_h */
