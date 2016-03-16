#pragma once

#include "GameConstants.h"
#include "Core/TTConstants.h"
#include "AI/TNode.h"
#include <cmath> 

const static int kMapRows = kScreenHeight / kCellHeight;
const static int kMapCols = kScreenWidth / kCellWidth;

class Map
{

private: 

	TNode map[kMapRows][kMapCols];

public:
	Map();
	~Map();
	void Init();
	void MarkNodeAsSolid(TNode node);
	TNode GetNode(int i, int j);
};

