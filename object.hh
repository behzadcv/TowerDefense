#ifndef TOWER_DEFENCE_OBJECT_HH
#define TOWER_DEFENCE_OBJECT_HH

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <utility>
#include "ui.hh"
#include <cstdlib>
//#include "context.hh"

//class GameContext;

template <typename T>
std::string toString(const T& v)
{
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

typedef enum 
    	{
        	Tow,
        	Monst
    	}ObjectType;

typedef enum 
    	{
        	Air,
        	Ground,
        	Mixed
    	}AttackType;

//Tower Shooting mode, user defined, defaultly it shoots at first
typedef enum 
    	{
            First,
            Highest,
            Fastest
    	}Mode;

//Monster Properties
typedef enum 
    	{
        	Fly,
        	Walk
    	}MoveType;
 
class Object
{
public:
    	//Constructor, width and height in user interface, it will be constant.
    	Object(std::pair<int, int>&);
    
    	//Virtual Destructor, if the map has a map with all objects, then map will have a destructor that deletes them..
    	//virtual ~Object(){}
    
	ObjectType getObjectType() const;
 
	std::string getDescription() const;

    	std::pair<int, int> getTilePosition() const;
    
    	sf::Vector2f getCenterPosition() const;
    
    	//draw objects in update at every tower and monster object seperately. it should be in every monster,tower seperately.
    	virtual void update(float) =0;
protected:
        std::pair<int, int> tile_position;
	ObjectType obtype;
    	std::string description;
        sf::Vector2f center_position;
};

#endif
