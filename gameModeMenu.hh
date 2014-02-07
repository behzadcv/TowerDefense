#ifndef TOWER_DEFENCE__GAMEMODEMENU_HH
#define TOWER_DEFENCE__GAMEMODEMENU_HH

#include "menu.hh"

// Class for start game menu
class GameModeMenu:public Menu
{

public:
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
};

#endif
