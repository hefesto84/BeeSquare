//
//  PlayState.cpp
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include "PlayState.h"

PlayState::PlayState ()
: m_background("board.png", kScreenWidth, kScreenHeight, kAnchor_bottom | kAnchor_left)
{
    SetGameState(kState_anyKeyToStart);
}

PlayState::~PlayState ()
{

}

void PlayState::Init ()
{

}

void PlayState::SetGameState (GameState state)
{
    m_gameState = state;
    if(m_gameState == kState_anyKeyToStart)
    {
        m_uiManager.UpdateMaxScore();
        m_uiManager.SetMessage(kPressToContinueText);
    }
    else if(m_gameState == kState_playing)
    {
        m_uiManager.SetCurrentScore(0);
        m_uiManager.SetMessage("");
        m_enemies.NextEnemy();
        m_player.ResetMovement();
		m_player.ResetTrail();
    }
}

void PlayState::Update (float deltaTime)
{
    if(m_gameState == kState_anyKeyToStart)
    {
        if(m_pressedKeys & (1 << kKeySpace))
        {
            SetGameState(kState_playing);
        }
    }
    else if(m_gameState == kState_playing)
    {
        m_player.UpdateMovement(deltaTime, m_holdKeys);
        m_player.Update(deltaTime);
        m_enemies.Update(deltaTime);
        
        if(m_enemies.EnemyEscaped())
        {
            SetGameState(kState_anyKeyToStart);
        }   

		if (m_player.IsPendingClosedPath()){
			m_enemies.WasEnemyTrailed();
		}
		
    }
    
    UpdateKeyEvents();
}

void PlayState::Render ()
{
    m_background.Render();
    m_enemies.Render();
    m_player.Render();
    m_uiManager.Render();
}
