//
//  Enemy.cpp
//  TechTest
//
//  Created by DavidFlix on 12/01/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#include "Enemy.h"
#include "AI/TPathfinder.h"

Enemy::Enemy ()
: m_sprite("enemyBlue.png")
{
    SetRandomPosition();
}

Enemy::~Enemy ()
{

}

void Enemy::SetRandomPosition ()
{
    m_sprite.SetPosition(SCREEN_TO_WORLD((rand() % (kScreenWidth / 2)) + (kScreenWidth / 4)), SCREEN_TO_WORLD((rand() % (kScreenHeight / 2)) + (kScreenHeight / 4)));
	printf("%d\n", m_sprite.GetPosX());
}

void Enemy::Escape ()
{
    m_sprite.SetPosition(SCREEN_TO_WORLD(kScreenWidth * 2), 0.0f);
}

void Enemy::Update (float deltaTime)
{
	//m_sprite.SetPosition(m_sprite.GetPosX() + 0.5f, m_sprite.GetPosY());
}

void Enemy::Render ()
{
    m_sprite.Render();
}

bool Enemy::FindEscapePath(){
	TNode enemyNode;
	float x = m_sprite.GetPosX() / kCellWidth;
	float y = m_sprite.GetPosY() / kCellHeight;
	enemyNode.i = y;
	enemyNode.j = x;
	TNode outNode;
	enemyNode.i = 0;
	enemyNode.j = 0;
	TPathfinder::GetInstance()->FindPath(enemyNode, outNode);
	return false;
}