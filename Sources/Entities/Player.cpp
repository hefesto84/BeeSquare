//
//  Player.cpp
//  TechTest
//
//  Created by DavidFlix on 08/01/15.
//  Modified by DaniSanteugini on 31/12/15
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#include "Player.h"

Player::Player ()
: m_sprite("player.png")
{
	ResetTrail();
    ResetMovement();
}

Player::~Player ()
{

}

void Player::SetPosition (float newPosX, float newPosY)
{
    // check screen bounds
    float x0 = m_sprite.GetWidth() / 2.0f;
    float x1 = SCREEN_TO_WORLD(kScreenWidth) - (m_sprite.GetWidth() / 2.0f);
    float y0 = m_sprite.GetHeight() / 2.0f;
    float y1 = SCREEN_TO_WORLD(kScreenHeight) - (m_sprite.GetHeight() / 2.0f);
    if(newPosX < x0)
    {
        newPosX = x0;
    }
    else if(newPosX > x1)
    {
        newPosX = x1;
    }
    if(newPosY < y0)
    {
        newPosY = y0;
    }
    else if(newPosY > y1)
    {
        newPosY = y1;
    }
    
    // set position
    m_sprite.SetPosition(newPosX, newPosY);
}

void Player::ResetMovement ()
{
    m_sprite.SetPosition(SCREEN_TO_WORLD(kScreenWidth / 2.0f), SCREEN_TO_WORLD(kScreenHeight / 2.0f));

	// set last cell position
	m_last = CalculateCurrentCell();

	// Restarting displacement pair 
	m_displacement = std::make_pair(0, 0);
	m_velocity = std::make_pair(0, 0);

}

void Player::UpdateMovement (float deltaTime, int holdKeys)
{

    if(holdKeys & (1<< kKeyArrowRight))
    {
		m_displacement.first = m_displacement.first + 2.0f*deltaTime;
    }
    else if(holdKeys & (1<< kKeyArrowLeft))
    {
		m_displacement.first = m_displacement.first - 2.0f*deltaTime;
    }
    
    if(holdKeys & (1<< kKeyArrowUp))
    {
		m_displacement.second = m_displacement.second + 2.0f*deltaTime;
    }
    else if(holdKeys & (1<< kKeyArrowDown))
    {
		m_displacement.second = m_displacement.second - 2.0f*deltaTime;
    }

	if (holdKeys == 0){
		if (m_displacement.first > 0){
			m_displacement.first = m_displacement.first - 3.0f*deltaTime;
		}
		else{
			m_displacement.first = 0;
		}
		if (m_displacement.second > 0){
			m_displacement.second = m_displacement.second - 3.0f*deltaTime;
		}
		else{
			m_displacement.second = 0;
		}
	}

	m_sprite.SetPosition(m_sprite.GetPosX() + m_displacement.first, m_sprite.GetPosY() + m_displacement.second);

	/*
	if (abs((m_sprite.GetPosX() + m_displacement.first) - m_sprite.GetPosX()) < kMaxVelocity){
		m_sprite.SetPosition(m_sprite.GetPosX() + m_displacement.first, m_sprite.GetPosY() + m_displacement.second);
	}
	
	if (abs((m_sprite.GetPosY() + m_displacement.second) - m_sprite.GetPosY()) < kMaxVelocity){
		m_sprite.SetPosition(m_sprite.GetPosX() + m_displacement.first, m_sprite.GetPosY() + m_displacement.second);
	}
	*/
}

void Player::RenderTrail()
{
	m_trail.Render();
}

void Player::ResetTrail()
{
	m_trail.ClearTrail();
}

TTCell Player::CalculateCurrentCell()
{
	float x = m_sprite.GetPosX() / kCellWidth;
	float y = m_sprite.GetPosY() / kCellHeight;
	TTCell position = std::make_pair((int)x, (int)y);
	return position;
}

void Player::IsPlayerStopped()
{
	if ((m_displacement.first + m_displacement.second) == 0.0f){
		m_trail.ClearTrail();
	}
}

bool Player::IsPendingClosedPath(){
	return m_trail.IsPendingClosedPath();
}

bool Player::IsEnemyInTrail(Enemy* enemy)
{
	if (m_trail.IsPendingClosedPath()){
		printf("Player is checking if enemy was trailed: %d\n",enemy->GetPosX());
	}
	return false;
}

void Player::Update (float deltaTime)
{
	IsPlayerStopped();
	TTCell current = CalculateCurrentCell();
	if (m_last != current){
		m_last = current;
		m_trail.IncreaseTrail(m_last);
	}
}

void Player::Render ()
{
	RenderTrail();
	m_sprite.Render();
}
