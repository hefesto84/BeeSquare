//
//  TTFont.cpp
//  TechTest
//
//  Created by DavidFlix on 13/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#include "TTFont.h"
#include "Core/TTSprite.h"

TTFont::TTFont ()
{
    m_charSize = 0.0f;
}

TTFont::~TTFont ()
{
    for(auto iElement : m_charTable)
    {
        delete iElement.second;
    }
    
    m_charTable.clear();
}

void TTFont::InitFont (const std::string& filename, int numElementsPerRow, int gridSize)
{
    m_charSize = SCREEN_TO_WORLD(gridSize);
    const std::string fontChars = "pqrstuvwxyz{|}~  abcdefghijklmnoPQRSTUVWXYZ[ ]^_@ABCDEFGHIJKLMNO0123456789:;<=>? ! #$%&'()*+,-./";
    
    int x = 0;
    int y = 0;
    for(char c : fontChars)
    {
        if(m_charTable.count(c) == 0)
        {
            m_charTable[c] = new TTSprite(filename, x * gridSize, y * gridSize, gridSize, gridSize, kAnchor_left | kAnchor_top);
        }
        
        ++x;
        if(x >= numElementsPerRow)
        {
            x = 0;
            ++y;
        }
    }
}

void TTFont::Render (const std::string& text, float posX, float posY, int anchor)
{
    float textWidth = m_charSize * text.length();
    if(anchor & kAnchor_right)
    {
        posX -= textWidth;
    }
    else if(anchor & kAnchor_hCenter)
    {
        posX -= textWidth / 2.0f;
    }
    if(anchor & kAnchor_bottom)
    {
        posY += m_charSize;
    }
    else if(anchor & kAnchor_vCenter)
    {
        posY += m_charSize / 2.0f;
    }
    
    TTSprite* spaceSprite = m_charTable[' '];
    for(char c : text)
    {
        TTSprite* charSprite = spaceSprite;
        if(m_charTable.count(c) > 0)
        {
            charSprite = m_charTable[c];
        }
        
        charSprite->SetPosition(posX, posY);
        charSprite->Render();
        
        posX += m_charSize;
    }
}
