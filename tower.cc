#include "tower.hh"

//Tower Constructor
Tower::Tower(std::pair<int, int> &tile_position, baseWaves &wave) : Object(tile_position), wave(&wave) {
	obtype = ObjectType::Tow;
	smode = Mode::First;
	level = 0;
	selected = false;
}

AttackType Tower::getAttackType() const	{
	return attype;
}

std::string Tower::getName() const	{
	return name;
}

Mode& Tower::getMode()	{
	return smode;
}

float Tower::getCost() const	{
	return cost;
}

float Tower::getUpgradeCost() const	{
	return upgradecost;
}

float Tower::getSellCost() const	{
	return 0.85*getCost();
}

float Tower::getRange() const	{
	return range;
}

float Tower::getDamage() const	{
	return damage;
}

float Tower::getLevel()	const	{
	return level;
}

bool & Tower::isSelected()	{
	return selected;
}

void Tower::paused(float time_of_pause, float current_time)	{
	last_shot_time = current_time - (time_of_pause - last_shot_time);
}

std::vector<Monster*> Tower::inRange()	{
	//goes through the monsters vector and checks which monsters are in its range, then inserts pointers to them in a new vector
	std::vector<Monster*> inrange;
	std::list<Monster*>& monsters = wave->getCurrentWave().getMonstersList();
	sf::Vector2f currloc = getCenterPosition();	//tower position;
	if(getAttackType() == AttackType::Air)	{
		for(auto iter = monsters.begin(); iter != monsters.end(); iter++)	{
			if((*iter)->getMoveType() == MoveType::Fly)	{
				auto distance = sqrt(pow(currloc.x - (*iter)->getCenterPosition().x, 2) + pow(currloc.y - (*iter)->getCenterPosition().y, 2));
				if(distance <= getRange())	{
					inrange.push_back(*iter);
				}
			}
		}
	}
	else if(getAttackType() == AttackType::Ground)	{
		for(auto iter = monsters.begin(); iter != monsters.end(); iter++)	{
			if((*iter)->getMoveType() == MoveType::Walk)	{
				auto distance = sqrt(pow(currloc.x - (*iter)->getCenterPosition().x, 2) + pow(currloc.y - (*iter)->getCenterPosition().y, 2));
				if(distance <= getRange())	{
					inrange.push_back(*iter);
				}
			}
		}
	}
	else	{
		for(auto iter = monsters.begin(); iter != monsters.end(); iter++)	{
			auto distance = sqrt(pow(currloc.x - (*iter)->getCenterPosition().x, 2) + pow(currloc.y - (*iter)->getCenterPosition().y, 2));
			if(distance <= getRange())	{
				inrange.push_back(*iter);
			}
		}
	}
	return inrange;
}

Monster* Tower::findFirst()	{
	std::vector<Monster*> inrange = inRange();
	std::vector<Monster*>::iterator it;
	float distance_traveled = 0;
	for(auto iter = inrange.begin(); iter != inrange.end(); iter++)	{
		if((*iter)->getDistanceTraveled() > distance_traveled)	{
			it = iter;
			distance_traveled = (*iter)->getDistanceTraveled();
		}
	}
	if(distance_traveled)
		return *it;
	return NULL;
}

Monster* Tower::findHighest()	{
	std::vector<Monster*> inrange = inRange();
	std::vector<Monster*>::iterator it;
	float highest = 0;
	for(auto iter = inrange.begin(); iter != inrange.end(); iter++)	{
		if((*iter)->getHealth() > highest)	{
			it = iter;
			highest = (*iter)->getHealth();
		}
	}
	if(highest)
		return *it;
	return NULL;
}

Monster* Tower::findFastest()	{
	std::vector<Monster*> inrange = inRange();
	std::vector<Monster*>::iterator it;
	float fastest = 0;
	for(auto iter = inrange.begin(); iter != inrange.end(); iter++)	{
		if((*iter)->getSpeed() > fastest)	{
			it = iter;
			fastest = (*iter)->getSpeed();
		}
	}
	if(fastest)	{
		return *it;
	}
	return NULL;
}


/*TowerA functions  begin----------------THIS IS THE ICE TOWER*/
TowerA::TowerA(std::pair<int, int> &tile_position, baseWaves &wave) : Tower(tile_position, wave)  {
	name  = "Ice Tower";
	description = "This is Tower A";
	attype = AttackType::Ground;
	cost = 150;
	upgradecost = 3*cost;
	range = T_RANGE;
	damage = 35;
	reload_time = 1.5; //CHECK THIS!
	last_shot_time = 0;
	slowing = 0.25;
	slowing_time = 2;
}

float TowerA::getSlowing() const	{
	return slowing;
}

float TowerA::getSlowingTime() const	{
	return slowing_time;
}

void TowerA::update(float frametime)   {
	//draws the tower
	if(selected)
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel(), true, getName(), toString(getSellCost()), toString(getUpgradeCost()), getRange() );
	else
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel());

	/* NOTE: The monsters should be added to the monsters vector so that the first one on screen is also the first in the vector.
	 * 	 This way if the mode is Highest/Fastest and all monsters have the same Health/Speed then the tower would shoot at the 			 *	 first. However, if they travel at different speeds then the a monster added later than the first might become the first 			 *	 one in the line. If it has as much health as the others the tower will not shoot at it...How to implement???  */
	if((frametime - last_shot_time) >= reload_time)	{
		//thisUI.drawAtPositionLevel(getTilePosition(), getLevel());		
		//last_shot_time = frametime;
		if(getMode() == Mode::First)	{
			auto it = findFirst();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}

		else if(getMode() == Mode::Highest)	{
			auto it = findHighest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	
		else if(getMode() == Mode::Fastest)	{
			auto it = findFastest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	}
}

void TowerA::shoot(float time, Monster* monster)	{
	last_shot_time = time;
	bool killed = monster->getShot(time, getDamage(), getSlowing(), getSlowingTime());
	thisUI.animationBullet(getCenterPosition(), monster->getCenterPosition());
	if(killed)	{
		wave->getCurrentWave().killMonster(monster);
	}
}

void TowerA::upgrade()	{
	if(getLevel() == 0)	{
		level++;
		damage += 20;
		range += 60;
		cost += upgradecost;
		upgradecost *= 3;
		reload_time -= 0.15;
		slowing += 0.15;
		slowing_time += 1;
		selected = false;
	}
	else if(getLevel() == 1)	{
		level++;
		damage += 50;
		range += 75;	
		reload_time -= 0.35;
		slowing += 0.2;
		slowing_time += 1.5;
		cost += upgradecost;
		selected = false;
	}
}

/*TowerA functions  end------------------*/

/*TowerB functions  begin----------------THIS IS THE FIRE TOWER*/
TowerB::TowerB(std::pair<int, int> &tile_position, baseWaves &wave) : Tower(tile_position, wave)  {
	name  = "Fire Tower";
	description = "This is Tower B";
	attype = AttackType::Air;
	cost = 100;
	upgradecost = 3*cost;
	range = T_RANGE;
	damage = 25;
	reload_time = 1; //CHECK THIS!
	last_shot_time = 0;
	freeze_time = 2;
	chance = 10;
}

float TowerB::getFreezeTime() const	{
	return freeze_time;
}

void TowerB::update(float frametime)   {
	//draws the tower
	if(selected)
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel(), true, getName(), toString(getSellCost()), toString(getUpgradeCost()), getRange() );
	else
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
	

	/* NOTE: The monsters should be added to the monsters vector so that the first one on screen is also the first in the vector.
	 * 	 This way if the mode is Highest/Fastest and all monsters have the same Health/Speed then the tower would shoot at the 			 *	 first. However, if they travel at different speeds then the a monster added later than the first might become the first 			 *	 one in the line. If it has as much health as the others the tower will not shoot at it...How to implement???  */
	if((frametime - last_shot_time) >= reload_time)	{
		//thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
		//last_shot_time = frametime;

		if(getMode() == Mode::First)	{
			auto it = findFirst();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}

		else if(getMode() == Mode::Highest)	{
			auto it = findHighest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	
		else	{
			auto it = findFastest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	}
}

void TowerB::shoot(float time, Monster* monster)	{
	last_shot_time = time;
	bool killed;
	int number = rand() % 100 + 1;	//random number from 1 to 100
	if(number <= chance)	{	//if number under the chance, it freezes the monster
		killed = monster->getShot(time, getDamage(), 0, 0, getFreezeTime());
	}
	else
		killed = monster->getShot(time, getDamage(), 0, 0);
	if(killed)	{
		wave->getCurrentWave().killMonster(monster);
	}
	thisUI.animationBullet(getCenterPosition(), monster->getCenterPosition());
}

void TowerB::upgrade()	{
	if(getLevel() == 0)	{
		level++;
		damage += 17;
		range += 85;
		cost += upgradecost;
		upgradecost *= 3;
		reload_time -= 0.15;
		freeze_time += 1;
		chance += 7;
		selected = false;
	}
	else if(getLevel() == 1)	{
		level++;
		damage += 40;
		range += 100;
		reload_time -= 0.2;
		freeze_time += 2;
		chance += 15;
		cost += upgradecost;
		selected = false;
	}
}


/*TowerB functions  end------------------*/

/*TowerC functions  begin----------------THIS IS THE MAGIC TOWER*/
TowerC::TowerC(std::pair<int, int> &tile_position, baseWaves &wave) : Tower(tile_position, wave)  {
	name  = "Magic Tower";
	description = "This is Tower C";
	attype = AttackType::Air;
	cost = 350;
	upgradecost = 3*cost;
	range = T_RANGE;
	damage = 65;
	reload_time = 3; //CHECK THIS!
	last_shot_time = 0;
	freeze_time = 3;
	slowing = 0.25;
	slowing_time = 2;
	chance = 13;
}

float TowerC::getSlowing() const	{
	return slowing;
}

float TowerC::getSlowingTime() const	{
	return slowing_time;
}

float TowerC::getFreezeTime() const	{
	return freeze_time;
}

void TowerC::update(float frametime)   {
	//draws the tower
	if(selected)
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel(), true, getName(), toString(getSellCost()), toString(getUpgradeCost()), getRange() );
	else
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
	

	/* NOTE: The monsters should be added to the monsters vector so that the first one on screen is also the first in the vector.
	 * 	 This way if the mode is Highest/Fastest and all monsters have the same Health/Speed then the tower would shoot at the 			 *	 first. However, if they travel at different speeds then the a monster added later than the first might become the first 			 *	 one in the line. If it has as much health as the others the tower will not shoot at it...How to implement???  */
	if((frametime - last_shot_time) >= reload_time)	{
		//thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
		//last_shot_time = frametime;

		if(getMode() == Mode::First)	{
			auto it = findFirst();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}

		else if(getMode() == Mode::Highest)	{
			auto it = findHighest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	
		else	{
			auto it = findFastest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	}
}

void TowerC::shoot(float time, Monster* monster)	{
	last_shot_time = time;
	bool killed;
	int number = rand() % 100 + 1;	//random number from 1 to 100
	if(number <= chance)	{	//if number under the chance, it freezes the monster
		killed = monster->getShot(time, getDamage(), getSlowing(), getSlowingTime(), getFreezeTime(), 0);
	}
	else	{
		killed = monster->getShot(time, getDamage(), getSlowing(), getSlowingTime(), 0, 0);	
	}
	if(killed)	{
		wave->getCurrentWave().killMonster(monster);
	}
	thisUI.animationBullet(getCenterPosition(), monster->getCenterPosition());
}

void TowerC::upgrade()	{
	if(getLevel() == 0)	{
		level++;
		damage += 50;
		range += 50;
		cost += upgradecost;
		upgradecost *= 4;	
		reload_time -= 0.35;
		selected = false;
		freeze_time += 1;
		slowing += 0.15;
		slowing_time += 1;
		chance += 7;
	}
	else if(getLevel() == 1)	{
		level++;
		attype = AttackType::Mixed;
		reload_time -= 0.5;
		damage += 80;
		range += 80;
		cost += upgradecost;
		selected = false;
		freeze_time += 2;
		slowing += 0.20;
		slowing_time += 2;
		chance += 15;
	}
}


/*TowerC functions  end------------------*/

/*TowerD functions  begin----------------THIS IS THE HARD DEFENCE TOWER*/
TowerD::TowerD(std::pair<int, int> &tile_position, baseWaves &wave) : Tower(tile_position, wave)  {
	name  = "Hard Defence";
	description = "This is Tower D";
	attype = AttackType::Ground;
	cost = 500;
	upgradecost = 3*cost;
	range = T_RANGE;
	damage = 90;
	reload_time = 4; //CHECK THIS!
	last_shot_time = 0;
	splash_radius = 80;	//opponents less than 20 units away from hit target take damage too
	reverse_time = 2;	//opponents less than 20 units away from hit target take damage too
	chance = 15;
}

float TowerD::getSplashRadius() const	{
	return splash_radius;
}

float TowerD::getReverseTime() const	{
	return reverse_time;
}

void TowerD::update(float frametime)   {
	//draws the tower
	if(selected)
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel(), true, getName(), toString(getSellCost()), toString(getUpgradeCost()), getRange() );
	else
		thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
	

	/* NOTE: The monsters should be added to the monsters vector so that the first one on screen is also the first in the vector.
	 * 	 This way if the mode is Highest/Fastest and all monsters have the same Health/Speed then the tower would shoot at the 			 *	 first. However, if they travel at different speeds then the a monster added later than the first might become the first 			 *	 one in the line. If it has as much health as the others the tower will not shoot at it...How to implement???  */
	if((frametime - last_shot_time) >= reload_time)	{
		//thisUI.drawAtPositionLevel(getTilePosition(), getLevel());
		//last_shot_time = frametime;

		if(getMode() == Mode::First)	{
			auto it = findFirst();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}

		else if(getMode() == Mode::Highest)	{
			auto it = findHighest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	
		else	{
			auto it = findFastest();
			if(it != NULL)	{	//NOTE, how to check if it points to anything?
				shoot(frametime, it);
			}
		}
	}
}

void TowerD::shoot(float time, Monster* monster)	{
	last_shot_time = time;
	bool killed;
	int number = rand() % 100 + 1;	//random number from 1 to 100
	if(number <= chance)	{	//if number under the chance, it freezes the monster
		killed = monster->getShot(time, getDamage(), 0, 0, 0, getReverseTime());
	}
	else
		killed = monster->getShot(time, getDamage());
	if(killed)	{
		wave->getCurrentWave().killMonster(monster);
	}
	thisUI.animationBullet(getCenterPosition(), monster->getCenterPosition());
	/*Looks for monsters around the shot monster and damages them too*/
	sf::Vector2f splash_center = monster->getCenterPosition();
	std::list<Monster*> monsters = wave->getCurrentWave().getMonstersList();
	for(auto iter = monsters.begin(); iter != monsters.end(); iter++)	{
		if(*iter != monster) 	{
			bool killed1 = false;
			auto distance = sqrt(pow(splash_center.x - (*iter)->getCenterPosition().x, 2) + pow(splash_center.y - (*iter)->getCenterPosition().y, 2));
			if(distance <= splash_radius && (*iter)->getMoveType() == MoveType::Walk)	{
				killed1 = (*iter)->getShot(time, getDamage()/2);
				if(killed1)	{
					wave->getCurrentWave().killMonster(*iter);
				}
			}
		}
	}
}

void TowerD::upgrade()	{
	if(getLevel() == 0)	{
		level++;
		damage += 100;
		range += 55;
		cost += upgradecost;
		upgradecost *= 4;	
		reload_time -= 0.4;
		selected = false;
		splash_radius += 40;	//opponents less than 20 units away from hit target take damage too
		reverse_time += 1;
		chance += 10;

	}
	else if(getLevel() == 1)	{
		level++;
		attype = AttackType::Mixed;
		damage += 130;
		range += 75;
		cost += upgradecost;
		reload_time -= 0.75;
		selected = false;
		splash_radius += 60;	//opponents less than 20 units away from hit target take damage too
		reverse_time += 1.5;
		chance += 15;
	}
}


/*TowerD functions  end------------------*/
