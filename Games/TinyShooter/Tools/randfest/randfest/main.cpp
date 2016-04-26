//
//  main.cpp
//  randfest
//
//  Created by Magnus Runesson on 2016-04-26.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
	// insert code here...
	int i;
	for( i=0; i<64; i++ )
	{
		/*
		// Star positions
		//int r = (rand() >> 23)-127;
		int r = (rand() & 65535) - 32767;
		/*/
		// Star speeds
		int r = -32 - (rand() & 127);
		/**/
		
		printf("%i,\n", r );
	}
    return 0;
}
