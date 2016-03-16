//
//  TTFont.h
//  TechTest
//
//  Created by DavidFlix on 13/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__TTFont__
#define __TechTest__TTFont__

#include "Core/TTConstants.h"

class TTSprite;

class TTFont
{

private:
    std::unordered_map<char, TTSprite*> m_charTable;
    float m_charSize;
    
public:
    TTFont ();
    ~TTFont ();
    
    void InitFont (const std::string& filename, int numElementsPerRow, int gridSize);
    void Render (const std::string& text, float posX, float posY, int anchor = (kAnchor_left | kAnchor_top));
};

#endif /* defined(__TechTest__TTFont__) */
