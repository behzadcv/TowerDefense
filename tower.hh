#ifndef TOWER_DEFENCE_TOWER_HH
#define TOWER_DEFENCE_TOWER_HH

#include "object.hh"
#include "wave.hh"

class Tower : public Object
{
public:

    	//Tower Constructor
    	Tower(std::pair<int, int>&, baseWaves&);

    	//Disallow copy assignment and copy constructor
    	Tower(const Tower&) = delete;
    	Tower& operator=(const Tower&) = delete;

	AttackType getAttackType() const;

	std::string getName() const;

	Mode& getMode();

	float getCost() const;

	float getUpgradeCost() const;

	float getSellCost() const;

	float getRange() const;

	float getDamage() const;

	float getLevel() const;

	bool & isSelected();

	virtual void upgrade() =0;

	std::vector<Monster*> inRange();

	Monster* findFirst();

	Monster* findHighest();

	Monster* findFastest();

	void paused(float, float);

	virtual void update(float) =0;
	virtual void shoot(float, Monster*) =0;

protected:
    	/* Every tower has: name, description, position, attacktype, cost, range, damage and level of update.
     	* const std::string name;              inheritted from Object;
     	* const std::string description;       inheritted from Object;
     	*/
    	AttackType attype;
	std::string name;
	Mode smode;
	baseWaves* wave;
    	float cost;
	float upgradecost;
    	float range;
    	float damage;
    	float level;
    	float reload_time;
	float last_shot_time;
	bool selected;

};

	/* Each tower will have five upgrade levels. For every tower we have a different class, say second level of Tower A will have a 	 * class of its own called Tower AA, third one Tower AAA etc.
 	 * Each tower type has its own update function, own UI. Say Tower A has as private member towerAUI thisUI. Tower AA has         	 * towerAAUI thisUI, Tower B has towerBUI thisUI etc. If we have a total of
         * three different towers and four upgades, meaning that with starting level of 0 the last tower level is 4, then there
         * must be 15 tower(?)UI's for the towers.
         */

//Tower A: speciel effect, slows monsters down
class TowerA : public Tower
{
public:
    	//Constructor
    	TowerA(std::pair<int, int>&, baseWaves&);

	float getSlowing() const;

	float getSlowingTime() const;

    	void update(float);

	void shoot(float, Monster*);

	void upgrade();
private:
    	towerAUI thisUI;
    	float slowing;		//slowing amount
	float slowing_time;	//slowing time, i.e. how long the monster is slowed for

};


//Tower B: freezes the monster at a 10% chance on hit for some 2 secs for example
class TowerB : public Tower
{
public:
	//Constructor
	TowerB(std::pair<int, int>&, baseWaves&);

	float getFreezeTime() const;

    	void update(float);

	void shoot(float, Monster*);

	void upgrade();
private:
    	towerCUI thisUI;
	float freeze_time;
	int chance;

};

//Tower C: freezes and slows at a 10% chance on hit for 2 secs
class TowerC : public Tower
{
public:
	TowerC(std::pair<int, int>&, baseWaves&);

	float getSlowing() const;

	float getSlowingTime() const;

    	float getFreezeTime() const;

    	void update(float);

	void shoot(float, Monster*);

	void upgrade();
private:
    	towerBUI thisUI;
	float slowing;
	float slowing_time;
	float freeze_time;
	int chance;

};

//Tower D: splash damage, when it hits one opponent, surrounding ones are damaged also
class TowerD : public Tower
{
public:
	TowerD(std::pair<int, int>&, baseWaves&);

	float getSplashRadius() const;

	float getReverseTime() const;

    	void update(float);

	void shoot(float, Monster*);

	void upgrade();
private:
    	towerDUI thisUI;
	float splash_radius;
	float reverse_time;
	int chance;

};
/*
//Tower E: Confuses monsters, reverses their direction for a short while
class TowerE : public Tower
{
public:
	TowerE(std::pair<int, int>&, defaultWaves&);

	float getReverseTime() const;

    	void update(float);

	void shoot(float, Monster*);
private:
    	towerCUI thisUI;
	float reverse_time;

};
*/

#endif
