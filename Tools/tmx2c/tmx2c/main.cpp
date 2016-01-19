//
//  main.cpp
//  tmx2c
//
//  Created by Magnus Runesson on 2016-01-02.
//  Copyright © 2016 Magnus Runesson. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class CTileMap
{
public:
	int Width;
	int Height;
	unsigned short* Tiles;
};

class CGameObjectTemplate
{
public:
	int WorldPosX;
	int WorldPosY;
	const char* ImageName;
};

class CScene
{
public:
	const char* TileBankName;
	const char* TileMapName;
	CTileMap* TileMap;
	int NumGameObjects;
	list<CGameObjectTemplate*> GameObjectTemplates;
};

const char* GetTileMapSymbol( const char* _pszSymbol )
{
	return _pszSymbol;
}

char symbol[ 1024 ];

const char* GetTilesSymbol( const char* _pszSymbol )
{
	sprintf( symbol, "%s_tiles", _pszSymbol );
	return (const char*)symbol;
}

const char* GetSceneSymbol( const char* _pszSymbol )
{
	sprintf( symbol, "%s_scene", _pszSymbol );
	return (const char*)symbol;
}

CScene* ParseMapElement( const XMLElement* _pNode );

const char* GetTileBankName( const XMLElement* _pElement )
{
	const XMLElement* tilesetImage = _pElement->FirstChildElement();
	const XMLAttribute* attribute = tilesetImage->FirstAttribute();
	while( attribute != NULL )
	{
		if( strcmp( "source", attribute->Name()) == 0 )
		{
			//
			// "source" attribute, i.e. the name of the tilebank
			//
			const char* ret = attribute->Value();
			printf("Tileset name: %s\n", ret );
			return ret;
		}
		
		attribute = attribute->Next();
	}

	return NULL;
}

unsigned short* ParseLayerCSV( const char* _pszLayerCSV )
{
	//printf("ParseLayerCSV data: %s\n", _pszLayerCSV );

	vector<int> retVector;

	std::string str = _pszLayerCSV;
	std::stringstream ss(str);
	
	unsigned int i;
	
	while (ss >> i)
	{
		//printf("i=%i\n", i );
		retVector.push_back(i);
		
		if((ss.peek() == ',') || (ss.peek() == 0x0a))
			ss.ignore();
	}
	
	int size = (int)retVector.size();
	printf("return size=%i\n", size );
	
	unsigned short* pret = new unsigned short[ size ];
	
	for( i=0; i<size; i++ )
	{
		unsigned int r = retVector[ i ];
		unsigned short w = 0;
		unsigned int tileindex = r & 0x0fffffff;
		bool flipX = (r & 0x80000000) == 0x80000000;
		bool flipY = (r & 0x40000000) == 0x40000000;
		bool flipD = (r & 0x20000000) == 0x20000000;
		w = tileindex & 0x1fff;
		if( flipX ) w |= 0x8000;
		if( flipY ) w |= 0x4000;
		if( flipD ) w |= 0x2000;
		//printf( "tile %i=0x%04x\n", i, w );
		pret[ i ] = w;
	}
	
	return pret;
}

CTileMap* ParseLayerElement( const XMLElement* _pElement )
{
	CTileMap* ret = new CTileMap();

	printf("element=%s\n", _pElement->Value());
	ret->Width = _pElement->IntAttribute( "width" );
	ret->Height = _pElement->IntAttribute( "height" );
	printf( "Map width=%i, height=%i\n", ret->Width, ret->Height );
	
	const XMLElement* dataElement = _pElement->FirstChildElement();
	ret->Tiles = ParseLayerCSV( dataElement->GetText());

	return ret;
}

CScene* ParseMapElement( const XMLElement* _pElement )
{
	printf("Parsing map node, woop!\n");

	CScene* ret = new CScene();
	
	const XMLElement* child = _pElement->FirstChildElement();
	while( child != NULL )
	{
		printf("Child: %s\n", child->Name());

		if( 0 == strcmp( "tileset", child->Name()))
			ret->TileBankName = GetTileBankName( child );
		
		if( 0 == strcmp( "layer", child->Name()))
			ret->TileMap = ParseLayerElement( child );

		child = child->NextSiblingElement();
	}
	
	return ret;
}

/*
void WriteScene( FILE* _pFile, CScene* _pScene, const char* _pszSymbolBase )
{
	fprintf( _pFile, "CScene %s = \n" );
	fprintf( _pFile, "{\n" );
}
*/

void WriteCHeader( FILE* _pFile, const char* _pszInFileName, const char* _pszSymbolBase )
{
	fprintf( _pFile, "//\n" );
	fprintf( _pFile, "// Data file generated from %s\n", _pszInFileName );
	fprintf( _pFile, "//\n" );
	fprintf( _pFile, "\n" );
	fprintf( _pFile, "#include \"types.h\"\n" );
	fprintf( _pFile, "#include \"TileMap.h\"\n" );
	fprintf( _pFile, "\n" );
}

void WriteTiles( FILE* _pFile, CTileMap* _pTileMap, const char* _pszSymbolBase )
{
	fprintf( _pFile, "uint16 %s[] =\n", GetTilesSymbol( _pszSymbolBase ));
	fprintf( _pFile, "{\n" );
	int x, y;
	int i = 0;
	for( y=0; y<_pTileMap->Height; y++ )
	{
		fprintf( _pFile, "\t" );
		for( x=0; x<_pTileMap->Width; x++ )
		{
			fprintf( _pFile, "%i,", _pTileMap->Tiles[ i ]-1);
			i++;
		}
		fprintf( _pFile, "\n" );
	}
	fprintf( _pFile, "};\n" );
	fprintf( _pFile, "\n" );
}

void WriteTileMap( FILE* _pFile, CTileMap* _pTileMap, const char* _pszSymbolBase )
{
	fprintf( _pFile, "CTileMap %s =\n", _pszSymbolBase );
	fprintf( _pFile, "{\n" );
	fprintf( _pFile, "\t%i,%i,\n", _pTileMap->Width, _pTileMap->Height );
	fprintf( _pFile, "\t0,\n" ); // Padding
	fprintf( _pFile, "\t(uint16*)&%s,\n", GetTilesSymbol( _pszSymbolBase ));
	fprintf( _pFile, "};\n" );
	fprintf( _pFile, "\n" );
}

FILE* OpenCFile( const char* _pszOutNameBase )
{
	char name[ 2048 ];
	sprintf( name, "%s.cpp", _pszOutNameBase );
	FILE* ret = fopen( name, "w" );
	return ret;
}

FILE* OpenHFile( const char* _pszOutNameBase )
{
	char name[ 2048 ];
	sprintf( name, "%s.h", _pszOutNameBase );
	FILE* ret = fopen( name, "w" );
	return ret;
}

void WriteHFile( FILE* _pFile, const char* _pszInFileName, const char* _pszSymbolBase )
{
	fprintf( _pFile, "//\n" );
	fprintf( _pFile, "// Data file generated from %s\n", _pszInFileName );
	fprintf( _pFile, "//\n" );
	fprintf( _pFile, "#ifndef %s_header_\n", _pszSymbolBase );
	fprintf( _pFile, "#define %s_header_\n", _pszSymbolBase );
	fprintf( _pFile, "\n" );
	fprintf( _pFile, "#include \"types.h\"\n" );
	fprintf( _pFile, "#include \"TileMap.h\"\n" );
	fprintf( _pFile, "\n" );
	fprintf( _pFile, "extern CTileMap %s;\n", GetTileMapSymbol( _pszSymbolBase ));
	fprintf( _pFile, "\n" );
	fprintf( _pFile, "#endif // %s_header_\n", _pszSymbolBase );
}


int main( int _numArgs, const char * _apszArg[])
{
	if( _numArgs != 4 )
	{
		printf("ERROR:\n");
		printf("  tmx2c <infile.tmx> <outfile_name_base> <out_symbol_name>\n");
		return -1;
	}
	
	const char* pszInFileName = _apszArg[ 1 ];
	const char* pszOutFileNameBase = _apszArg[ 2 ];
	const char* pszOutSymbolName = _apszArg[ 3 ];
	
	XMLDocument mapDocument;
	mapDocument.LoadFile( pszInFileName );
	
	if( mapDocument.Error())
	{
		printf("Load error in file %s\n", pszInFileName );
		printf("Error: %s\n", mapDocument.ErrorName());
		return -2;
	}
	
	CScene* scene = NULL;
	const XMLElement* element = mapDocument.FirstChildElement();
	while( element != NULL )
	{
		printf( "element: %s\n", element->Value());
		if( strcmp( "map", element->Value()) == 0 )
		{
			//
			// This is the map node
			//
			scene = ParseMapElement( element );
		}
		element = element->NextSiblingElement();
	}
	
	FILE* f;

	//
	// Write C file
	//
	f = OpenCFile( pszOutFileNameBase );
	WriteCHeader( f, pszInFileName, pszOutSymbolName );
	WriteTiles( f, scene->TileMap, pszOutSymbolName );
	WriteTileMap( f, scene->TileMap, pszOutSymbolName );
	fclose( f );

	//
	// Write header file
	//
	f = OpenHFile( pszOutFileNameBase );
	WriteHFile( f, pszInFileName, pszOutSymbolName );
	fclose( f );
	
	return 0;
}
