#include "Entities/Cell.h"

Cell::Cell() : m_sprite("cell.png")
{

}

Cell::~Cell()
{
	m_sprite.ReleaseSprites();
}

void Cell::SetPosition(float newPosX, float newPosY)
{

	m_sprite.SetPosition(newPosX, newPosY);
}

void Cell::Update(float deltaTime)
{

}

void Cell::Render()
{
	m_sprite.Render();
}