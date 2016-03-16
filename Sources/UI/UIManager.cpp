//
//  UIManager.cpp
//  TechTest
//
//  Created by DavidFlix on 27/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#include "UIManager.h"
#include "GameConstants.h"

UIManager::UIManager ()
{
    m_score = 0;
    m_maxScore = 0;
    m_message = "";
    m_showMessage = false;
    m_font.InitFont("font.png", 16, 25);
}

UIManager::~UIManager ()
{
    
}

void UIManager::SetMessage (const std::string& message)
{
    m_message = message;
    m_showMessage = (m_message.length() > 0);
}

void UIManager::SetCurrentScore (int score)
{
    m_score = score;
}

void UIManager::IncreaseScore ()
{
    m_score++;
}

void UIManager::UpdateMaxScore ()
{
    if(m_score > m_maxScore)
    {
        m_maxScore = m_score;
    }
}

void UIManager::Render ()
{
    std::string enemiesCounter = kScoreText + std::to_string(m_score);
    m_font.Render(enemiesCounter, SCREEN_TO_WORLD(kTextScreenMargin), SCREEN_TO_WORLD(kTextScreenMargin), kAnchor_left | kAnchor_bottom);
    
    std::string enemiesMaxCounter = kMaxScoreText + std::to_string(m_maxScore);
    m_font.Render(enemiesMaxCounter, SCREEN_TO_WORLD(kScreenWidth - kTextScreenMargin), SCREEN_TO_WORLD(kTextScreenMargin), kAnchor_right | kAnchor_bottom);
    
    if(m_showMessage)
    {
        m_font.Render(m_message, SCREEN_TO_WORLD(kScreenWidth / 2.0f), SCREEN_TO_WORLD(kScreenHeight / 2.0f), kAnchor_hCenter | kAnchor_vCenter);
        
    }
}
