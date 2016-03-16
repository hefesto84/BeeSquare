//
//  Player.h
//  TechTest
//
//  Created by DavidFlix on 08/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__Player__
#define __TechTest__Player__

#include "Core/TTEntity.h"
#include "Core/TTSprite.h"
#include "Entities/Trail.h"
#include "Entities/Cell.h"
#include "Entities/Enemy.h"

typedef std::pair<float, float> TTDisplacement;
typedef std::pair<float, float> TTVelocity;

/* 

	Calculating velocity limits:

	maxV = 300px/sec
	timeDelta = 1/60 = 0.016

	maxDisplacement => x = 300*0.016 => x = 4.8

	If m_displacement > 4.8 => velocity limit reached

*/

const float kMaxVelocity = 2.0f;

class Player : public TTEntity
{
    
private:
    
	/// Player sprite
    TTSprite m_sprite;

	/// Player trail
	Trail m_trail;

	/// Player last cell position
	TTCell m_last;

	/// Player displacement
	TTDisplacement m_displacement;

	/// Player velocity
	TTVelocity m_velocity;

	// Pending closed trail
	bool isPendingClosedPath = false;

public:
    Player ();
    ~Player ();
    
    void SetPosition (float posX, float posY);
    void Update (float deltaTime);
    void ResetMovement ();
    void UpdateMovement (float deltaTime, int holdKeys);
    void Render ();
	void ResetTrail();
	bool IsEnemyInTrail(Enemy* enemy);
	bool IsPendingClosedPath();
private:
	void RenderTrail();
	void IsPlayerStopped();
	
	TTCell CalculateCurrentCell();
};

#endif /* defined(__TechTest__Player__) */
