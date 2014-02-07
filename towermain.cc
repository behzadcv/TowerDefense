#include "tower.hh"

int main()
{
	//Initialization of TowerA
	const ObjectType tow_type = ObjectType::Tow;
   	const std::string tow_desc = "This Magic Tower is the best tower in the world!";
	const float cost = 100;
	const float range = 25;
	const float damage = 50;
	const float level = 0; 
	const float slows = 25;   	
	//sf::Vector2f new_Pos(100,100);
	std::pair<int, int> tow_tile_loc(1, 1);
	TowerA newTower(tow_type, tow_desc, tow_tile_loc, cost, range, damage, level, slows);

	//Initialization of Monster Boss
	const ObjectType mon_type = ObjectType::Monst;
   	const std::string mon_desc = "The worst Boss of all!";
	//sf::Vector2f mon_Pos(100,120);
	std::pair<int, int> mon_tile_loc(2, 1);
	const float health = 250;
	const float speed = 20;
	const float armor = 10;
	Boss newBoss(mon_type, mon_desc, mon_tile_loc, health, speed, armor);

	std::pair<int, int> curr_pos = newTower.getTilePosition();
	if(newTower.getAttackType() == AttackType::Air && newTower.getMode() == Mode::First)	{
		std::cout << "Description: " << newTower.getDescription() << std::endl;
		std::cout << "Position: (" << curr_pos.first << ", " << curr_pos.second << ")"<< std::endl;
		std::cout << "Cost: " << newTower.getCost() << std::endl;
		std::cout << "Range: " << newTower.getRange() << std::endl;
		std::cout << "Damage: " << newTower.getDamage() << std::endl;
		std::cout << "Slows: " << newTower.getSlowing() << std::endl;
		std::cout << "Level: " << newTower.getLevel() << std::endl;
		std::cout << "Upgrading the tower:"<< std::endl;
		newTower.upgrade();
		std::cout << "The Tower is now level: " << newTower.getLevel() <<"\n" << std::endl;
			
	}
	if(newBoss.getMoveType() ==MoveType::Walk)	{
	std::cout << "Creating a new boss monster:"<< std::endl;
	std::cout << "Description: " << newBoss.getDescription() << std::endl;
	std::cout << "Position: (" << newBoss.getTilePosition().first << ", " << newBoss.getTilePosition().second << ")"<< std::endl;
	std::cout << "Health: " << newBoss.getHealth() << std::endl;
	std::cout << "Speed: " << newBoss.getSpeed() << std::endl;
	std::cout << "Distance Traveled: " << newBoss.getDistanceTraveled() << std::endl;
	std::cout << "Travelling: " << std::endl;
	newBoss.update();
	std::cout << "Distance Traveled: " << newBoss.getDistanceTraveled() << std::endl;
	std::cout << "Checking if there is a Monster in Range!" << std::endl;
	newTower.update();
	std::cout << "Monster is in range! It will get hit and slowed" << std::endl;
	std::cout << "Health after hit: " << newBoss.getHealth() << std::endl;
	std::cout << "Speed after hit: " << newBoss.getSpeed() << std::endl;
	}
    	return 0;
}
