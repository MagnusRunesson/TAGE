//
//  TinyRaceCar.hpp
//  TinyArcade
//
//  Created by Magnus Runesson on 2015-12-08.
//  Copyright © 2015 Magnus Runesson. All rights reserved.
//

#ifndef TinyRaceCar_hpp
#define TinyRaceCar_hpp

#include "Gameobject.h"
#include "FixedPoint.h"
#include "fp2d.h"
#include "types.h"
#include "SpriteRenderer.h"

class TinyRaceCar
{
public:
	TinyRaceCar();
	
	void Create();
	void Destroy();
	
	void PreRender();
	void Update();

	void SetPosition( int _x, int _y );
	inline int GetWorldPositionX() { return m_gameObject->GetWorldPositionX(); }
	inline int GetWorldPositionY() { return m_gameObject->GetWorldPositionY(); }
	
private:
	GameObject* m_gameObject;
	
	// Car properties
	FixedPoint m_acceleration;
	FixedPoint m_brake;
	FixedPoint m_maxSpeed;
	FixedPoint m_speedDamping;
	FixedPoint m_turn;
	
	// Runtime state
	FixedPoint m_speed;
	FixedPoint m_angle;
	fp2d m_direction;
	fp2d m_position;
	
	// Render information
	int m_drawAngle;

	void ApplyMovement();
	void DoSpeed();
	void DoTurning();

};

#endif /* TinyRaceCar_hpp */
