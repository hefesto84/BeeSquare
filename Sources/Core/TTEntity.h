//
//  TTEntity.h
//  TechTest
//
//  Created by DavidFlix on 08/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTEntity__
#define __TechTest__TTEntity__

class TTEntity
{

public:
    TTEntity ();
    virtual ~TTEntity ();
    
    virtual void Update (float deltaTime) = 0;
    virtual void Render () = 0;
    
};

#endif /* defined(__TechTest__TTEntity__) */
