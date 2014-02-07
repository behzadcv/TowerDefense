#ifndef TOWER_DEFENCE__MAINMENU_HH
#define TOWER_DEFENCE__MAINMENU_HH

#include "menu.hh"

// Class for main menu
class MainMenu:public Menu
{

public:
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
};

#endif

