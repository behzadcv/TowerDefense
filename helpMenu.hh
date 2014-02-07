#ifndef TOWER_DEFENCE__HELPMENU_HH
#define TOWER_DEFENCE__HELPMENU_HH

#pragma once
#include "menu.hh"

// Class for Help menu
class HelpMenu:public Menu
{

public:
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
};

#endif
