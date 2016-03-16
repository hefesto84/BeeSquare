//
//  Trail.h
//  TechTest
//
//  Created by DaniSanteugini on 31/12/15.
//  Copyright (c) 2015 Bee Square. All rights reserved.
//

#ifndef __TechTest__Trail__
#define __TechTest__Trail__

#include "Core/TTConstants.h"
#include "Entities/Cell.h"
#include <map>

typedef std::pair<Cell*, TTCell> CellTTCell;

class Trail
{

private:
	std::vector<CellTTCell> m_trail;
	bool pendingClosedPath = false;
public:
	Trail();
	virtual ~Trail();
	void ClearTrail();
	void IncreaseTrail(TTCell cell);
	bool IsPendingClosedPath();
	bool IsEnemyWrapped();
	bool IsEnemyTrailed(TTCell cell);
	void Render();
};

#endif /* defined(__TechTest__Trail__) */