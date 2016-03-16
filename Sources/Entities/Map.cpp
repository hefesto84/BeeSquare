#include "Map.h"


Map::Map()
{
	
}


Map::~Map()
{

}

void Map::MarkNodeAsSolid(TNode node){
	int i = node.i;
	int j = node.j;
	map[i][j].isSolid = node.isSolid;
}

TNode Map::GetNode(int i, int j){
	return map[i][j];
}

void Map::Init(){
	for (int i = 0; i < kMapRows; i++){
		for (int j = 0; j < kMapCols; j++){
			map[i][j].isSolid = false;
			map[i][j].i = i;
			map[i][j].j = j;
		}
	}
}