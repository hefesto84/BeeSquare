//
//  TTTextureLibrary.h
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTTextureLibrary__
#define __TechTest__TTTextureLibrary__

#include "TTConstants.h"

class TTTexture;

class TTTextureLibrary
{
    
private:
    /// Loaded textures table
    std::unordered_map<std::string, TTTexture*> m_textures;
    
public:
    
    TTTextureLibrary ();
    ~TTTextureLibrary ();
    
    TTTexture* LoadTexture (const std::string& imageName);
    
};

#endif /* defined(__TechTest__TTTextureLibrary__) */
