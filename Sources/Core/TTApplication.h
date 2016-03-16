//
//  TTApplication.h
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTApplication__
#define __TechTest__TTApplication__

#include "TTConstants.h"

class TTState;

class TTApplication
{
    
private:
    SDL_GLContext m_glContext;
    SDL_Window* m_window;
    TTState* m_currentState;
    bool m_finishApplication;
    
public:
    TTApplication ();
    ~TTApplication ();
  
    void InitApplication ();
    void ReleaseApplication ();
    inline bool ApplicationIsRunning ();
    
    void SetState (TTState* state);
    
    void Update (float deltaTime);
    void Render ();
    
private:
    void HandleEvents ();
    void HandleKeyDown (const SDL_Keysym& keysym);
    void HandleKeyUp (const SDL_Keysym& keysym);
    inline void StopApplication ();
    
};

bool TTApplication::ApplicationIsRunning ()
{
    return !m_finishApplication;
}

void TTApplication::StopApplication ()
{
    m_finishApplication = true;
}

#endif /* defined(__TechTest__TTApplication__) */
