//
//  GameConstants.h
//  TechTest
//
//  Created by DavidFlix on 27/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef TechTest_GameConstants_h
#define TechTest_GameConstants_h

#include "Core/TTConstants.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constants
//////////////////////////////////////////////////////////////////////////////////////////////////////////

static const std::string kPressToContinueText = "- Press SPACE to start -";
static const std::string kScoreText = "Score: ";
static const std::string kMaxScoreText = "Max Score: ";

static const int kTextScreenMargin = 25;

static const int kWaitTimeForNextMonster = 2;
static const int kMaxTimeToCatchTheMonster = 15;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enums
//////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    kState_anyKeyToStart = 0,
    kState_playing
} GameState;

typedef enum
{
    kEnemiesState_waitingForNext = 0,
    kEnemiesState_catchTheMonster,
    kEnemiesState_escape
} EnemiesState;

typedef enum
{
	kEmpty = 0,
	kEnemy = 0,
	kTrail = 0,
	kPlayer = 0

}NodeState;

#endif
