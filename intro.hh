#ifndef TOWER_DEFENCE__INTRO_HH
#define TOWER_DEFENCE__INTRO_HH

#include "menu.hh"

//Class for the first screen after starting game 
class Intro:public Menu
{
public:
	
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int , int ){return Nothing;}
};

#endif
