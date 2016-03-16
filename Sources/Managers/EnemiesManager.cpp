//
//  EnemiesManager.cpp
//  TechTest
//
//  Created by DavidFlix on 27/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#include "EnemiesManager.h"
#include "Entities/Enemy.h"

EnemiesManager::EnemiesManager ()
{
    m_enemiesBuffer = new Enemy();
    NextEnemy();
}

EnemiesManager::~EnemiesManager ()
{
    delete m_enemiesBuffer;
    m_enemiesBuffer = NULL;
    m_currentEnemy = NULL;
}

void EnemiesManager::LaunchNewEnemy ()
{
    m_currentEnemy = m_enemiesBuffer;
    m_currentEnemy->SetRandomPosition();
}

void EnemiesManager::NextEnemy ()
{
    m_currentEnemy = NULL;
    SetState(kEnemiesState_waitingForNext);
}

bool EnemiesManager::EnemyEscaped ()
{
    if(m_currentEnemy && (m_state == kEnemiesState_escape))
    {
        float x0 = m_currentEnemy->GetPosX() - (m_currentEnemy->GetWidth() / 2.0f);
        float x1 = m_currentEnemy->GetPosX() + (m_currentEnemy->GetWidth() / 2.0f);
        float y0 = m_currentEnemy->GetPosY() - (m_currentEnemy->GetHeight() / 2.0f);
        float y1 = m_currentEnemy->GetPosY() + (m_currentEnemy->GetHeight() / 2.0f);
        return ((x0 < 0) || (x1 > SCREEN_TO_WORLD(kScreenWidth)) || (y0 < 0) || (y1 > SCREEN_TO_WORLD(kScreenHeight)));
    }
    
    return false;
}

Enemy* EnemiesManager::GetCurrentEnemy(){
	return m_currentEnemy;
}

bool EnemiesManager::WasEnemyTrailed(){
	printf("was enemy trailed? %d\n");
	m_currentEnemy->FindEscapePath();
	return false;
}

void EnemiesManager::SetState (EnemiesState state)
{
    m_state = state;
    m_timer = SDL_GetTicks();
}

void EnemiesManager::Update (float deltaTime)
{
    if(m_currentEnemy)
    {
        m_currentEnemy->Update(deltaTime);
    }
    
    if(m_state == kEnemiesState_waitingForNext)
    {
        float secondsPassed = (SDL_GetTicks() - m_timer) / 1000.0f;
        if(secondsPassed >= kWaitTimeForNextMonster)
        {
            LaunchNewEnemy();
            SetState(kEnemiesState_catchTheMonster);
        }
    }
    else if(m_state == kEnemiesState_catchTheMonster)
    {
        float secondsPassed = (SDL_GetTicks() - m_timer) / 1000.0f;
        if(secondsPassed >= kMaxTimeToCatchTheMonster)
        {
            m_currentEnemy->Escape();
            SetState(kEnemiesState_escape);
        }
    }
}

void EnemiesManager::Render ()
{
    if(m_currentEnemy)
    {
        m_currentEnemy->Render();
    }
}
