#ifndef MONSTERS_HH
#define MONSTERS_HH

#include "monster.hh"

class infinityMonster : public Monster {
public:
	infinityMonster(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);

	bool getSlowImmunity();

private:
	monsterAUI thisUI;
	bool slow_immunity;
};

class infinityMonster2 : public Monster {
public:
	infinityMonster2(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);
	bool getSlowImmunity();

private:
	monsterBUI thisUI;
	bool slow_immunity;
};

class infinityMonsterF1 : public Monster {
public:
	infinityMonsterF1(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);
	bool getSlowImmunity();

private:
	monsterFAUI thisUI;
	bool slow_immunity;
};

class infinityMonsterF2 : public Monster {
public:
	infinityMonsterF2(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);
	bool getSlowImmunity();

private:
	monsterFBUI thisUI;
	bool slow_immunity;
};

class infinityBossMonster : public Monster {
public:
	infinityBossMonster(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);

	bool getSlowImmunity();

private:
	monsterBossUI thisUI;
	bool slow_immunity;
};

class infinityBossMonsterImmune : public Monster {
public:
	infinityBossMonsterImmune(std::pair<int, int>, path_type, float, MoveType, float hp, float mhp, float sp, float sOD, float mOD);

	void draw(sf::Vector2i,float, int, int);

	bool getSlowImmunity();

private:
	monsterBossUI thisUI;
	bool slow_immunity;
};

class easyWalking1 : public Monster {
public:
	easyWalking1( std::pair<int, int>, path_type, float );
	void draw(sf::Vector2i,float,int, int);
	bool getSlowImmunity();


private:
	monsterAUI thisUI;
	bool slow_immunity;
};

class easyWalking2 : public Monster {
public:
	easyWalking2( std::pair<int, int>, path_type, float );
	void draw(sf::Vector2i,float,int, int);
	bool getSlowImmunity();
private:
	monsterBUI thisUI;
	bool slow_immunity;
};

class easyFlying1 : public Monster {
public:
	easyFlying1( std::pair<int, int>, path_type, float );
	void draw(sf::Vector2i,float,int, int);
	bool getSlowImmunity();
private:
	monsterFAUI thisUI;
	bool slow_immunity;
};

class easyFlying2 : public Monster {
public:
	easyFlying2( std::pair<int, int>, path_type, float );
	void draw(sf::Vector2i,float,int, int);
	bool getSlowImmunity();
private:
	monsterFBUI thisUI;
	bool slow_immunity;
};

class Boss : public Monster	{
public:
	Boss(std::pair<int, int>, path_type, float);

	float getArmor() const;

	void draw(sf::Vector2i,float,int, int);
	bool getSlowImmunity();

	//void update( float, tdMap& ){};
	//void update( float ){}

private:
	monsterBossUI thisUI;
	float armor;
	bool slow_immunity;
};



#endif

