#include "TPathfinder.h"

const int kDiagonalMovementCost = 14;
const int kOrthogonalMovementCost = 10;


TPathfinder* TPathfinder::p_instance = NULL;

TPathfinder* TPathfinder::GetInstance(){
	if (!p_instance){
		p_instance = new TPathfinder();
	}
	return p_instance;
}

TTNeighbours TPathfinder::getNeighbours(TNode node){
	TTNeighbours neighbours;
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			if (i == 0 && j == 0){
				continue;
			}
			int iref = node.i + i;
			int jref = node.j + j;
			
			if (iref >= 0 && iref < kMapRows && jref >= 0 && jref < kMapCols){
				TNode n = this->map.GetNode(iref, jref);
				neighbours.push_back(n);
			}
		}
	}
	return neighbours;
}

int TPathfinder::getDistance(TNode from, TNode to){
	int distance = 0;

	int dstI = std::abs(from.i - to.i);
	int dstJ = std::abs(from.j - to.j);

	if (dstI > dstJ){
		return kDiagonalMovementCost * dstJ + kOrthogonalMovementCost * (dstI - dstJ);
	}
	else{
		return kDiagonalMovementCost * dstI + kOrthogonalMovementCost * (dstJ - dstI);
	}

	return distance;
}
bool TPathfinder::listContains(List nodes, TNode node){

	bool found = false;
	
	for (int i = 0; i < nodes.size(); i++){
		if (node.i == nodes.at(i).i && node.j == nodes.at(i).j){
			found = true;
			break;
		}
	}

	return found;

}

TTPath TPathfinder::tracePath(TNode from, TNode to){
	List path;
	
	TNode currentNode = to;
	
	printf("Added step to the path: %d,%d\n",currentNode.parent->i,currentNode.parent->j);
	currentNode = *currentNode.parent;
	printf("Added step to the path: %d,%d\n", currentNode.parent->i, currentNode.parent->j);

	while (currentNode.i != from.i && currentNode.j != from.j){
		printf("Added step to the path\n");
		path.push_back(currentNode);
		currentNode = *currentNode.parent;

	}
	
	return path;
}

void TPathfinder::InitMap(){
	this->map.Init();
}

void TPathfinder::MarkNodeAsSolid(TNode node){
	this->map.MarkNodeAsSolid(node);
}

bool TPathfinder::FindPath(TNode from, TNode to){

	TTPath path;
	List openedList;
	List closedList;

	openedList.push_back(from);
	
	while (!openedList.empty()){

		TNode currentNode = openedList.at(0);

		for (int i = 0; i < openedList.size(); i++){
			TNode node = openedList.at(i);
		
			if (node.F < currentNode.F || (node.F == currentNode.F && node.H < currentNode.H)){
				currentNode = node;
			}
		}
		
		openedList.erase(openedList.begin());
		closedList.push_back(currentNode);

		if (currentNode.i == to.i && currentNode.j == to.j){
			printf("Path found!\n");
			return true;
			//path = tracePath(from, *currentNode.parent);
			//return path;
		}

		TTNeighbours neighboursList = getNeighbours(currentNode);
	
		for (List::iterator it = neighboursList.begin(); it != neighboursList.end(); it++){
			TNode node = *it;

			if (node.isSolid || listContains(closedList, node)){
				continue;
			}

			int movementCost = currentNode.G + getDistance(currentNode, node);

			if (movementCost < node.G || !listContains(openedList, node)){
				node.G = movementCost;
				node.H = getDistance(node, to);
			

				node.parent = &currentNode;
				
				if (!listContains(openedList, node)){
					openedList.push_back(node);
				}
			}
		}
	}
	printf("Path not found");
	return false;
}