#pragma once
#include "Core/TTConstants.h"
#include "AI/TNode.h"
#include "Entities/Map.h"

typedef std::vector<TNode> List; 
typedef std::vector<TNode> TTPath;
typedef std::vector<TNode> TTNeighbours;

class TPathfinder
{

private:
	static TPathfinder *p_instance;
	Map map;

public:

	static TPathfinder* GetInstance();

private:

	TPathfinder(){
		printf("TPathfinder singleton created.\n");
	}

	TTNeighbours getNeighbours(TNode node);
	bool listContains(List nodes, TNode node);
	int getDistance(TNode from, TNode to);
	TTPath tracePath(TNode from, TNode to);

public:

	bool FindPath(TNode from, TNode to);
	void MarkNodeAsSolid(TNode node);
	void InitMap();

};

