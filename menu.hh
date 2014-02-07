#ifndef TOWER_DEFENCE__MENU_HH
#define TOWER_DEFENCE__MENU_HH

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/System.hpp>
#include <list>
#include <stdio.h>
#include <iostream>
#include "ui.hh"

// Base abstract class of menus for definitions
class Menu
{

public:
	/* types of responces on user clicking in menus */
	enum MenuResult { Nothing, Exit, PlayInf, PlayArc, PlayNorm,Help, HighScores, ToMenu, GameModeMenu, Continue };	
	/* struct for saving buttons coordinates and their responces */
	struct MenuItem
		{
		public:
			sf::Rect<int> rect;
			MenuResult action;
		};
	
	virtual MenuResult Show(sf::RenderWindow& window)=0;
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);

protected:
	std::list<MenuItem> _menuItems;

};






#endif
