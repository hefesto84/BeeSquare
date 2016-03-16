//
//  TTState.cpp
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include "TTState.h"

TTState::TTState ()
{
    m_holdKeys = 0;
    m_pressedKeys = 0;
    m_releasedKeys = 0;
}

TTState::~TTState ()
{
    
}

void TTState::HandleKey (SDL_EventType keyEvent, SDL_Keycode key)
{
    if(keyEvent == SDL_KEYDOWN)
    {
        int keyMask = KeyCodeToMask(key);
        if(!(m_holdKeys & keyMask))
        {
            m_pressedKeys |= keyMask;
            m_holdKeys |= keyMask;
        }
    }
    else if(keyEvent == SDL_KEYUP)
    {
        int keyMask = KeyCodeToMask(key);
        m_pressedKeys &= ~keyMask;
        m_holdKeys &= ~keyMask;
        m_releasedKeys |= keyMask;
    }
}

void TTState::UpdateKeyEvents ()
{
    m_releasedKeys = 0;
    m_pressedKeys = 0;
}

int TTState::KeyCodeToMask (SDL_Keycode key)
{
    if(key == SDLK_UP)
    {
        return (1 << kKeyArrowUp);
    }
    else if(key == SDLK_DOWN)
    {
        return (1 << kKeyArrowDown);
    }
    else if(key == SDLK_LEFT)
    {
        return (1 << kKeyArrowLeft);
    }
    else if(key == SDLK_RIGHT)
    {
        return (1 << kKeyArrowRight);
    }
    else if(key == SDLK_SPACE)
    {
        return (1 << kKeySpace);
    }
    
    return 0;
}