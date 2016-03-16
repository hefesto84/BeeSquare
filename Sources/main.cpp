//
//  main.cpp
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#include <SDL2/SDL.h>

#ifdef _WIN32
	#include <SDKDDKVer.h>
	#include <tchar.h>	
	#include <Windows.h>
	#include <gl\glew.h>
	#include <gl\gl.h> 
	#include <gl\glu.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Core/TTConstants.h"
#include "Core/TTApplication.h"
#include "States/PlayState.h"
#include "AI/TPathfinder.h"

int main( int argc, char* argv[] )
{
    TTApplication app;
    app.InitApplication();
    app.SetState(new PlayState());
    
    const Uint32 singleFrameTime = 1000 / kMaxFPS;
    Uint32 lastTime = SDL_GetTicks();
    
	TPathfinder *m_pathfinder = TPathfinder::GetInstance();
	m_pathfinder->InitMap();

	TNode from;
	TNode to;

	from.i = 0;
	from.j = 0;

	to.i = 0;
	to.j = 3;

	m_pathfinder->FindPath(from, to);

    while(app.ApplicationIsRunning())
    {
        Uint32 startTime = SDL_GetTicks();
        float deltaTime = ((startTime - lastTime) / 1000.0f);
        lastTime = startTime;
        
        app.Update(deltaTime);
        app.Render();
        
        Uint32 endTime = SDL_GetTicks();
        
        int remainingTime = singleFrameTime - (endTime - startTime);
        if(remainingTime > 0)
        {
            SDL_Delay(remainingTime);
        }
        
        //printf ("FPS: %f\n", 1.0f / deltaTime);
    }
    
    app.ReleaseApplication();
    return 0;
}
