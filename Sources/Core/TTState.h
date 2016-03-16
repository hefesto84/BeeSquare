//
//  TTState.h
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTState__
#define __TechTest__TTState__

#include "TTConstants.h"

class TTState
{
    
protected:
    int m_holdKeys;
    int m_pressedKeys;
    int m_releasedKeys;
    
public:
    TTState ();
    virtual ~TTState ();
    
    void HandleKey (SDL_EventType keyEvent, SDL_Keycode key);
    
    virtual void Init () = 0;
    virtual void Update (float deltaTime) = 0;
    virtual void Render () = 0;
    
protected:
    void UpdateKeyEvents ();
    
private:
    int KeyCodeToMask (SDL_Keycode key);
    
};

#endif /* defined(__TechTest__TTState__) */
