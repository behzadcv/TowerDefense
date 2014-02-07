#include "object.hh"
//#include "player.hh"
//#include "wave.hh"
//#include "context.hh"
//#include "ui.hh"

//a monster vector and tower vector that include all the monster and tower objects. Will be stored in map!
//std::vector<Monster*> monsters;
//std::vector<Tower*> towers;

    	//Constructor, width and height in user interface, it will be constant.
Object::Object(std::pair<int, int> &tile_position) : tile_position(tile_position){
	center_position.x = tile_position.first*85 + 42.5;
    	center_position.y = tile_position.second*85 + 82.5;
}

//upper margin 40pixels
//80x80 pixels

//Virtual Destructor, if the map has a map with all objects, then map will have a destructor that deletes them..
//virtual ~Object(){}

ObjectType Object::getObjectType() const	{
	return obtype;
}	

std::string Object::getDescription() const	{
	return description;
}

std::pair<int, int> Object::getTilePosition() const	{
	return tile_position;
}

sf::Vector2f Object::getCenterPosition() const  {
	return center_position;
}


	
