#ifndef TOWER_DEFENCE_CONTEXT_HH
#define TOWER_DEFENCE_CONTEXT_HH

#include<list>
//forward declaration of the Monster and Tower classes
class Tower;
class Monster;

class GameContext	{
public:
	GameContext(){
		//ints.push_back(5);
	}

	~GameContext(){
		
	}

	void addTower(Tower*);

	//void removeTower(std::pair<int, int>&);

	std::list<Monster*> getMonstersList(); //std::list<Monster*>& maybe?

	std::list<Tower*> getTowersList();	//std::list<Tower*>& maybe?

private:
	std::list<Monster*> monsters;
	std::list<Tower*> towers;
};
#endif
