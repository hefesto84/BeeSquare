//
//  TTApplication.cpp
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include "TTApplication.h"

#ifdef _WIN32
	#include <Windows.h>
	#include <gl\glew.h>
	#include <gl\gl.h>
	#include <gl\GLU.h>
	#include <gl\glext.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#include "TTState.h"
#include "TTSprite.h"

TTApplication::TTApplication ()
{
    m_window = NULL;
    m_currentState = NULL;
    m_finishApplication = false;
}

TTApplication::~TTApplication ()
{

}

void TTApplication::InitApplication ()
{
    // init sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        StopApplication();
    }

    // set window attributes
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    m_window = SDL_CreateWindow("Bee Square", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
    
    // init OpenGL
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.18f, 0.24f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    
#ifdef _WIN32
	glewInit();
#endif

     TTSprite::InitSprites();
}

void TTApplication::ReleaseApplication ()
{
    if(m_currentState)
    {
        delete m_currentState;
        m_currentState = NULL;
    }
    
    TTSprite::ReleaseSprites();
    
    SDL_GL_DeleteContext(m_glContext);
    SDL_Quit();
}

void TTApplication::HandleEvents ()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
            {
                // handle key presses
                HandleKeyDown(event.key.keysym);
                break;
            }
            case SDL_KEYUP:
            {
                // handle key releases
                HandleKeyUp(event.key.keysym);
                break;
            }
            case SDL_QUIT:
            {
                // handle quit requests
                StopApplication();
                break;
            }
        }
        
    }
}

void TTApplication::HandleKeyDown (const SDL_Keysym& keysym)
{
    if(keysym.sym == SDLK_ESCAPE)
    {
        StopApplication();
    }
    else
    {
        if(m_currentState)
        {
            m_currentState->HandleKey(SDL_KEYDOWN, keysym.sym);
        }
    }
}

void TTApplication::HandleKeyUp (const SDL_Keysym& keysym)
{
    if(keysym.sym != SDLK_ESCAPE)
    {
        if(m_currentState)
        {
            m_currentState->HandleKey(SDL_KEYUP, keysym.sym);
        }
    }
}

void TTApplication::SetState (TTState* state)
{
    m_currentState = state;
    m_currentState->Init();
}

void TTApplication::Update (float deltaTime)
{
    // process incoming events
    HandleEvents();
    
    // update current state
    if(m_currentState)
    {
        m_currentState->Update(deltaTime);
    }
}

void TTApplication::Render ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // render current state
    if(m_currentState)
    {
        m_currentState->Render();
    }
    
    // swap render buffer
    SDL_GL_SwapWindow(m_window);
}
