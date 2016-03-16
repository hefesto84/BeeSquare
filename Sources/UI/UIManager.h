//
//  UIManager.h
//  TechTest
//
//  Created by DavidFlix on 27/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__UIManager__
#define __TechTest__UIManager__

#include "Core/TTConstants.h"
#include "Core/TTFont.h"

class UIManager
{
    
private:
    /// Current score
    int m_score;
    
    /// Max score
    int m_maxScore;
    
    /// Message
    std::string m_message;
    bool m_showMessage;
    
    // UI font
    TTFont m_font;
    
public:
    UIManager ();
    ~UIManager ();
    
    void SetMessage (const std::string& message);
    void SetCurrentScore (int score);
    void IncreaseScore ();
    void UpdateMaxScore ();
    
    void Render ();
    
};

#endif /* defined(__TechTest__UIManager__) */
