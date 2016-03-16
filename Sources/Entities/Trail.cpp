#include "Entities/Trail.h"

Trail::Trail()
{
	
}

Trail::~Trail()
{

}

void Trail::ClearTrail(){
	m_trail.clear();
}

void Trail::IncreaseTrail(TTCell cell){
	bool canAdd = true;
	float x = (kCellWidth * cell.first);
	float y = (kCellHeight * cell.second);

	CellTTCell item;
	Cell *c = new Cell();
	c->SetPosition(x + kCellWidth*0.5, y + kCellHeight*0.5);
	item.first = c;
	item.second = cell;

	for (int i = 0; i < m_trail.size(); i++){
		if (m_trail.at(i).second.first == cell.first && m_trail.at(i).second.second == cell.second){
			canAdd = false;
			printf("Closed path\n");
			pendingClosedPath = true;
		}
	}
	
	if (canAdd){
		m_trail.push_back(item);
		printf("%d|%d\n", item.second.first, item.second.first);
	}

}

bool Trail::IsPendingClosedPath(){
	if (pendingClosedPath){
		pendingClosedPath = false;
		return true;
	}
	return false;
}

bool Trail::IsEnemyWrapped(){
	return false;
}

bool Trail::IsEnemyTrailed(TTCell cell)
{
	bool found = false;

	for (int i = 0; i < m_trail.size(); i++){
		if (m_trail.at(i).second.first == cell.first && m_trail.at(i).second.first == cell.second){
			printf("Enemy was trailed!\n");
			found = true;
			break;
		}
	}

	return found;
}

void Trail::Render(){

	// Performance issue. SDL is rendering entire screen even in not-modified zones
	for (std::vector<CellTTCell>::iterator it = m_trail.begin(); it != m_trail.end(); it++){
		it->first->Render();
	}
}