#include "player.hh"
#include <string>
#include <sstream>

//#include "context.hh"
/*
Player::Player(std::string &name="Dimitar") : name(name)	{
	money = 1000;
	score = 0;
}*/

Player::~Player(){
		while( towers.size() != 0 ){
			delete towers.back();
			towers.remove(towers.back());
			std::cout<< "Deleting towers!\n";
		}
}

std::string Player::getMoney()	{
	return toString(getMoneyF());
}

float Player::getMoneyF()	{
	return money;
}

void Player::giveMoney(float mon){
	money += mon;
}

void Player::giveScore(float sco){
	score += sco;
}

int& Player::getLives()	{
	return lives;
}

std::string Player::getLivesS()	{
	return toString(getLives());
}

std::string Player::getScore()	{
	return toString(getScoreF());
}

float Player::getScoreF()	{
	return score;
}

std::list<Tower*> Player::getTowersList()	{
		return towers;
}


/*arg: which tower, maybe using enums,

*/
std::string Player::buyTower(terrain type, std::pair<int, int>tile_position, baseWaves &wave)	{
	for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
		if((*iter)->getTilePosition().first == tile_position.first && (*iter)->getTilePosition().second == tile_position.second)	{
			return "Position occupied!";
		}
	}
	if(type==terrain::buyTowerB)	{
		if(getMoneyF() >= 150)	{	//if he has more money than TowerA costs
			towers.push_back(new TowerA(tile_position, wave));
			money-= 150;
			return "Ice Tower purchased!";
		}
	}
	else if(type==terrain::buyTowerA)	{
		if(getMoneyF() >= 350)	{	//if he has more money than TowerA costs
			towers.push_back(new TowerC(tile_position, wave));
			money-= 350;
			return "Magic Tower purchased!";
		}
	}
	else if(type==terrain::buyTowerC){
		if(getMoneyF() >= 100)	{	//if he has more money than TowerA costs
			towers.push_back(new TowerB(tile_position, wave));
			money-= 100;
			return "Fire Tower purchased!";
		}
	}
	else if(type==terrain::buyTowerD)	{
		if(getMoneyF() >= 500)	{	//if he has more money than TowerA costs
			towers.push_back(new TowerD(tile_position, wave));
			money-= 500;
			return "Hard Defence purchased!";
		}
	}
	return "Insufficient amout of money!";
}

std::string Player::sellTower(std::pair<int, int> cords)	{
	for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
		if((*iter)->getTilePosition().first == cords.first && (*iter)->getTilePosition().second == cords.second)	{
			money += 0.85*(*iter)->getCost();
			cancelSelection();
			delete(*iter);
			iter = towers.erase(iter);
			return "Tower sold!";

		}
	}
	return "Tower could not be sold!";
}

std::string Player::upgradeTower(Tower* tow)	{
	if(tow->getLevel() < 2)	{
		if(tow->getUpgradeCost() < money)	{
			money -= tow->getUpgradeCost();
			tow->upgrade();
			return "Tower upgraded!";
		}
		cancelSelection();
		return "Money insufficient for upgrade!";
	}
	else	{
		cancelSelection();
		return "Highest level reached!";
	}
}

bool Player::selectTower(std::pair<int, int>tile_index)	{
	for(auto iter = towers.begin(); iter != towers.end(); iter++)							{
		if((*iter)->getTilePosition() == tile_index)	{
			(*iter)->isSelected() = true;
			selected = (*iter);
			return true;
		}
	}
	return false;
}

std::string Player::cancelSelection()	{
	selected->isSelected() = false;
	selected = NULL;
	return "Selection Cancelled";
}

std::string Player::whichAction(int num)	{
	if(num == 0)
		return cancelSelection();
	else if(num == 1)
		return upgradeTower(selected);
	else if(num == 2)
		return sellTower(selected->getTilePosition());
	else
		return changeShootingMode(num);

}

std::string Player::changeShootingMode(int num)	{
	if(num == 3)	{
		selected->getMode() = Mode::First;
		cancelSelection();
		return "Shooting mode set to First";
	}
	else if(num == 4)	{
		selected->getMode() = Mode::Highest;
		cancelSelection();
		return "Shooting mode set to Highest";
	}
	else if(num == 5)	{
		selected->getMode() = Mode::Fastest;
		cancelSelection();
		return "Shooting mode set to Fastest";
	}
	return std::string();
}

void Player::paused(float time_of_pause, float current_time)	{
	for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
		(*iter)->paused(time_of_pause, current_time);
	}	
}

std::string Player::buyLive()	{
	if(getMoneyF() >= 1000)	{
		money -= 1000;
		lives++;
		return "Enjoy your new live!";
	}
	return "Insufficient money!";
}
