#ifndef TOWER_DEFENCE_PLAYER_HH
#define TOWER_DEFENCE_PLAYER_HH

#include "tower.hh"
#include<list>
#include "wave.hh"
class Tower;
class defaultWaves;
class Player
{
public:
	Player(const std::string &name="") : name(name)	{
	money = 700;
	score = 0;
	selected = NULL;
	lives = 10;
	}

	~Player();

	std::string getMoney();

	float getMoneyF();

	std::string getScore();

	float getScoreF();

	void giveMoney(float);

	void giveScore(float);

	int& getLives();

	std::string getLivesS();

	std::list<Tower*> getTowersList();

	std::string buyTower(terrain , std::pair<int, int>, baseWaves &);

	std::string sellTower(std::pair<int, int>);

	std::string upgradeTower(Tower*);

	bool selectTower(std::pair<int, int>);

	std::string cancelSelection();

	std::string whichAction(int);

	std::string changeShootingMode(int);

	void paused(float, float);
	
	void removeLive(){ lives--; }

	std::string buyLive();
private:
	//GameContext context;
	Tower *selected;
	const std::string name;
	float money;
	float score;
	int lives;
	std::list<Tower*> towers;

};

#endif
