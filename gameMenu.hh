#ifndef TOWER_DEFENCE__GAMEMENU_HH
#define TOWER_DEFENCE__GAMEMENU_HH

#include "menu.hh"

// Class for pause game menu
class GameMenu : public Menu
{
public:
	MenuResult Show(sf::RenderWindow& window);
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int , int ){return Nothing;}
};

#endif
