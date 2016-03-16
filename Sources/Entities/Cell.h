//
//  Cell.h
//  TechTest
//
//  Created by DaniSanteugini on 31/12/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__Cell__
#define __TechTest__Cell__

#include "Core/TTEntity.h"
#include "Core/TTSprite.h"

class Cell : public TTEntity
{

private:
	/// Cell sprite
	TTSprite m_sprite;
	
public:
	Cell();
	virtual ~Cell();
	void SetPosition(float posX, float posY);
	void Update(float deltaTime);
	void Render();
};

#endif /* defined(__TechTest__Cell__) */