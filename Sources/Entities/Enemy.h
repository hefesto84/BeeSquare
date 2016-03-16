//
//  Enemy.h
//  TechTest
//
//  Created by DavidFlix on 12/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__Enemy__
#define __TechTest__Enemy__

#include "Core/TTEntity.h"
#include "Core/TTSprite.h"
#include "Cell.h"

class Enemy : public TTEntity
{
    
private:
    /// Enemy sprite
    TTSprite m_sprite;
    
public:
    Enemy ();
    ~Enemy ();
    
    void Update (float deltaTime);
    void Render ();
    
    void Escape ();
    void SetRandomPosition ();
    
    inline float GetPosX ();
    inline float GetPosY ();
    inline float GetWidth ();
    inline float GetHeight ();

	bool FindEscapePath();
    
};

float Enemy::GetPosX ()
{
    return m_sprite.GetPosX();
}

float Enemy::GetPosY ()
{
    return m_sprite.GetPosY();
}

float Enemy::GetWidth ()
{
    return m_sprite.GetWidth();
}

float Enemy::GetHeight ()
{
    return m_sprite.GetHeight();
}

#endif /* defined(__TechTest__Enemy__) */
