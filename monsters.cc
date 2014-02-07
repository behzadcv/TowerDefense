#include "monsters.hh"

infinityMonster::infinityMonster(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = false;
}

void infinityMonster::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}
bool infinityMonster::getSlowImmunity()	{
	return slow_immunity;
}

infinityMonster2::infinityMonster2(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = false;
}

void infinityMonster2::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool infinityMonster2::getSlowImmunity()	{
	return slow_immunity;
}

infinityMonsterF1::infinityMonsterF1(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = false;
}

void infinityMonsterF1::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool infinityMonsterF1::getSlowImmunity()	{
	return slow_immunity;
}

infinityMonsterF2::infinityMonsterF2(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = false;
}

void infinityMonsterF2::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool infinityMonsterF2::getSlowImmunity()	{
	return slow_immunity;
}

infinityBossMonster::infinityBossMonster(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = false;
}

bool infinityBossMonster::getSlowImmunity()	{
	return slow_immunity;
}

void infinityBossMonster::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

infinityBossMonsterImmune::infinityBossMonsterImmune(std::pair<int, int> tile_position, path_type type, float frametime, MoveType mt, float hp, float mhp, float sp, float sOD, float mOD) : Monster(tile_position, type, frametime){
	description = "These monsters spawn from eternal depths of the Abyss. Their numbers are countless.";
	mtype = mt;
	health = hp;
	maxhealth = mhp;
	max_speed = sp;
	moneyOnDeath = mOD;
	scoreOnDeath = sOD;
	slow_immunity = true;
}

bool infinityBossMonsterImmune::getSlowImmunity()	{
	return slow_immunity;
}

void infinityBossMonsterImmune::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

easyWalking1::easyWalking1(std::pair<int, int> tile_position, path_type type, float frametime) : Monster(tile_position, type, frametime){
	description = "Plain and simple walking monster.";
	mtype = MoveType::Walk;
	health = 750;
	maxhealth = 750;
	max_speed = 150;
	moneyOnDeath = 10.0;
	scoreOnDeath = 10.0;
	slow_immunity = false;
}
void easyWalking1::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool easyWalking1::getSlowImmunity()	{
	return slow_immunity;
}

easyWalking2::easyWalking2(std::pair<int, int> tile_position, path_type type, float frametime) : Monster(tile_position, type, frametime){
	description = "Plain and simple walking monster with little more health";
	mtype = MoveType::Walk;
	health = 20;
	maxhealth = 20;
	max_speed = 2;
	slow_immunity = false;
}

void easyWalking2::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool easyWalking2::getSlowImmunity()	{
	return slow_immunity;
}

easyFlying1::easyFlying1(std::pair<int, int> tile_position, path_type type, float frametime) : Monster(tile_position, type, frametime){
	description = "This is easy monster on wings.";
	mtype = MoveType::Fly;
	health = 10;
	maxhealth = 10;
	max_speed = 60;
	slow_immunity = false;
}

void easyFlying1::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool easyFlying1::getSlowImmunity()	{
	return slow_immunity;
}

easyFlying2::easyFlying2(std::pair<int, int> tile_position, path_type type, float frametime) : Monster(tile_position, type, frametime){
	description = "This is easy monster on wings with little more health.";
	mtype = MoveType::Fly;
	health = 20;
	maxhealth = 20;
	max_speed = 80;
	slow_immunity = false;
}

void easyFlying2::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool easyFlying2::getSlowImmunity()	{
	return slow_immunity;
}

Boss::Boss(std::pair<int, int> tile_position, path_type type, float frametime) : Monster(tile_position, type, frametime)	{
	description = "This is the Boss Monster!";
	mtype = MoveType::Walk;
	health = 250;
	maxhealth = 250;
	max_speed = 100;
	armor = 10;
	slow_immunity = false;
}

void Boss::draw(sf::Vector2i pos, float speed,int direction, int health_bar)	{
	thisUI.drawAtPositionDirection(pos, speed, direction, health_bar);
}

bool Boss::getSlowImmunity()	{
	return slow_immunity;
}

float Boss::getArmor() const	{
	return armor;
}




