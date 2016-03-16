#pragma once
#include "Core/TTConstants.h"

class TNode
{
public:
	TNode();
	~TNode();
	bool isSolid = false;
	int i = 0;
	int j = 0;
	TNode* parent;
	int G = 0;
	int H = 0;
	int F = G + H;
};

