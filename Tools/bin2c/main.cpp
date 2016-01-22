//
//  main.cpp
//  bin2c
//
//  Created by Magnus Runesson on 22/01/16.
//  Copyright (c) 2016 Pokewhat. All rights reserved.
//

#include <stdio.h>

char filename[ 1024 ];
char* HeaderFileName( const char* _pszBase )
{
	sprintf( filename, "%s.h", _pszBase );
	return filename;
}

char* SourceFileName( const char* _pszBase )
{
	sprintf( filename, "%s.cpp", _pszBase );
	return filename;
}

int main( int argc, const char * argv[])
{
	if( argc != 4 )
	{
		printf("Usage: bin2c <infile> <outfile_base> <symbol>\n");
		return -1;
	}
	
	const char* pszInFileName = argv[ 1 ];
	const char* pszOutFileNameBase = argv[ 2 ];
	const char* pszOutSymbol = argv[ 3 ];
	
	FILE* f;
	
	//
	// Read the dat
	//
	f = fopen( pszInFileName, "r" );
	fseek( f, 0, SEEK_END );
	int size = (int)ftell( f );
	fseek( f, 0, SEEK_SET );
	unsigned char* pData = new unsigned char[ size ];
	fread( pData, 1, size, f );
	fclose( f );
	
	//
	// Write the header file
	//
	f = fopen( HeaderFileName( pszOutFileNameBase ), "w" );
	fprintf( f, "//\n" );
	fprintf( f, "// Generated from source file '%s'\n", pszInFileName );
	fprintf( f, "//\n" );
	fprintf( f, "\n");
	fprintf( f, "#ifndef __%s_h\n", pszOutSymbol );
	fprintf( f, "#define __%s_h\n", pszOutSymbol );
	fprintf( f, "\n");
	fprintf( f, "extern \"C\" const unsigned char %s[];\n", pszOutSymbol );
	fprintf( f, "\n");
	fprintf( f, "#endif // __%s_\n", pszOutSymbol );
	fprintf( f, "\n");
	fclose( f );
	
	//
	// Write the source file
	//
	f = fopen( SourceFileName( pszOutFileNameBase ), "w" );
	fprintf( f, "//\n" );
	fprintf( f, "// Generated from source file '%s'\n", pszInFileName );
	fprintf( f, "//\n" );
	fprintf( f, "\n" );
	fprintf( f, "extern \"C\" const unsigned char %s[];\n", pszOutSymbol );
	fprintf( f, "const unsigned char %s[] = {\n", pszOutSymbol );
	int i;
	for( i=0; i<size; i++ )
		fprintf( f, "\t0x%02x,\n", pData[ i ]);
	fprintf( f, "};\n" );
	fprintf( f, "\n" );
	fclose( f );
	
	// insert code here...
    return 0;
}
