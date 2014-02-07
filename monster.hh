#ifndef TOWER_DEFENCE_MONSTER_HH
#define TOWER_DEFENCE_MONSTER_HH

#include "object.hh"
#include "tdmap.hh"

typedef enum{
	up,
	down,
	left,
	right,
	same
}direction;

typedef enum{
	alive,
	dead
}status;

class Monster : public Object
{
public:
	Monster(std::pair<int, int>, path_type, float);

	//required for infinity mode
	//Monster(std::pair<int, int>&, path_type&, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);
	//****

	Monster(const Monster&) = delete;
   	Monster& operator=(const Monster&) = delete;
	virtual ~Monster(){}

	MoveType getMoveType() const;

	float getHealth() const;

	float getMaxHealth() const;

	float getSpeed() const;

	void paused(float);

	void reverse();

	float getDistanceTraveled() const;
	void update(float, tdMap&);  //dt is the clock time initialized in beginning game while loop as sf::Time dt = clock.restart();
	void update(float){}//magically this should go through g++
	void move(float, tdMap&);

	float getScore(){
		return scoreOnDeath;
	}
	float getMoney(){
		return moneyOnDeath;
	}

	virtual bool getSlowImmunity() =0;

	bool getShot(float time, float damage, float slowed1 =0, float slowed_for =0, float freeze_for =0, float reverse_time =0);
	virtual void draw(sf::Vector2i,float,int, int) =0;

protected:
	direction dir;
	status stat;
	direction lastdir;
	float distance_traveled;
	MoveType mtype;
	float health;
	float maxhealth;
	float speed;
	float max_speed;
	float last_moved;	//last time the monster moved, NOTE if monster frozen it is different than lastframe!
	//monsterAUI thisUI;
	float freeze_time;	//the time the monster has to stay frozen
	float slowed;		//how much the monster is slowed
	float slowed_until;	//the time before which the monster is slowed
	bool slowed_until_extended;	//if the freeze_time has been added to the slowed_until
	bool reversed;
	float reversed_until;
	float lastframe;	//previous frame of the game loop, i.e. time when the update was called last
	float scoreOnDeath;
	float moneyOnDeath;
};



#endif
