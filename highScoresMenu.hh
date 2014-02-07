#ifndef TOWER_DEFENCE__HIGHSCORESMENU_HH
#define TOWER_DEFENCE__HIGHSCORESMENU_HH

#include "menu.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Class for High scores menu
class HighScoresMenu:public Menu
{

public:
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	
};

#endif
