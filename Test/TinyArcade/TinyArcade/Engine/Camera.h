//
//  Camera.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

class Camera
{
public:
	Camera();
	
	void SetWorldPosition( int _x, int _y );
	inline int GetWorldX(){ return m_worldPositionX; }
	inline int GetWorldY(){ return m_worldPositionY; }

	static Camera* main;

private:
	int m_worldPositionX;
	int m_worldPositionY;
};

#endif /* Camera_hpp */
