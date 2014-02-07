#include "context.hh"


	void GameContext::addTower(Tower* tow)	{
		towers.push_back(tow);
	}

	/*void GameContext::removeTower(std::pair<int, int> &tow_tile_loc)	{
		for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
			if(((*iter)->getTilePosition().first == tow_tile_loc.first) && ((*iter)->getTilePosition().second == tow_tile_loc.second))	{
				towers.erase(iter);
				break;
			}
		}
	}*/

	std::list<Monster*> GameContext::getMonstersList()	{
		return monsters;
	}

	std::list<Tower*> GameContext::getTowersList()	{
		return towers;
	}

