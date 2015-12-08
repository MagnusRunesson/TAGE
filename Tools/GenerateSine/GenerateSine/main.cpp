//
//  main.cpp
//  GenerateSine
//
//  Created by Magnus Runesson on 2015-12-04.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[])
{
	FILE* f = fopen( "sinetable.cpp", "w" );
	
	fprintf( f, "#include \"types.h\"\n" );
	fprintf( f, "\n" );
	fprintf( f, "sint16[] sineTable =\n" );
	fprintf( f, "{\n" );
	
	float steps = 256.0f;
	float fullLoop = 360.0f;
	float da = 360.0f / steps;
	float a = 0.0f;
	int i = 0;
	
	while( a < fullLoop )
	{
		float s = sinf( a * (3.1415f/180.0f));
		int is = (int)((s * 256.0f) + 0.4f);
		fprintf( f, "\t%i,\t//angle=%.2f deg, sin=%.2f, index=%i\n", is, a, s, i );
		a += da;
		i++;
	}
	fprintf( f, "};\n" );
	fclose( f );
	
    return 0;
}
