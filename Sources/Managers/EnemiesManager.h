//
//  EnemiesManager.h
//  TechTest
//
//  Created by DavidFlix on 27/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__EnemiesManager__
#define __TechTest__EnemiesManager__

#include <SDL2/SDL.h>
#include "GameConstants.h"

class Enemy;

class EnemiesManager
{

private:
    /// Current enemy in screen
    Enemy* m_currentEnemy;
    
    /// Enemies buffer
    Enemy* m_enemiesBuffer;
    
    /// Timer variable
    Uint32 m_timer;
    
    /// Enemies manager state
    EnemiesState m_state;
    
public:
    EnemiesManager ();
    ~EnemiesManager ();
    
    void NextEnemy ();
    bool EnemyEscaped ();
    
    void Update (float deltaTime);
    void Render ();
    
	Enemy* GetCurrentEnemy();
	bool WasEnemyTrailed();

private:
    void SetState (EnemiesState state);
    void LaunchNewEnemy ();
    
};

#endif /* defined(__TechTest__EnemiesManager__) */
