//
//  PlayState.h
//  TechTest
//
//  Created by DavidFlix on 12/12/14.
//  Copyright (c) 2014 Bee Square. All rights reserved.
//

#ifndef __TechTest__PlayState__
#define __TechTest__PlayState__

#include "Core/TTState.h"
#include "Core/TTFont.h"
#include "Core/TTSprite.h"
#include "GameConstants.h"
#include "UI/UIManager.h"
#include "Managers/EnemiesManager.h"
#include "Entities/Player.h"
#include "Entities/Map.h"

class TTSprite;
class Player;

class PlayState : public TTState
{
    
private:
    TTSprite m_background;
    Player m_player;
    GameState m_gameState;
    UIManager m_uiManager;
    EnemiesManager m_enemies;
	Map m_map;

public:
    PlayState ();
    ~PlayState ();
    
    void Init ();
    void Update (float deltaTime);
    void Render ();
    
private:
    void SetGameState (GameState state);
    
};

#endif /* defined(__TechTest__PlayState__) */
