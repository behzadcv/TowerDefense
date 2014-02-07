
#include "gameModeMenu.hh"
#include "menu.hh"

/* Descr: Displaying start game menu window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult GameModeMenu::Show(sf::RenderWindow& window)
{

	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("src/images/game mode.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	// "Back" button coordinates
	MenuItem backButton4;
	backButton4.rect.top= 60;
	backButton4.rect.height = 80;
	backButton4.rect.left = 18;
	backButton4.rect.width = 112;
	backButton4.action = ToMenu;

	// "Infinity mode" button coordinates
	MenuItem infModeButton;
	infModeButton.rect.top= 450;
	infModeButton.rect.height = 150;
	infModeButton.rect.left = 150;
	infModeButton.rect.width = 210;
	infModeButton.action = PlayInf;

	// "Arcade mode" button coordinates
	MenuItem arcModeButton;
	arcModeButton.rect.top= 450;
	arcModeButton.rect.height = 150;
	arcModeButton.rect.left = 420;
	arcModeButton.rect.width = 210;
	arcModeButton.action = PlayArc;

	// "Normal mode" button coordinates
	MenuItem normModeButton;
	normModeButton.rect.top= 450;
	normModeButton.rect.height = 150;
	normModeButton.rect.left = 730;
	normModeButton.rect.width = 210;
	normModeButton.action = PlayNorm;

	// Putting new items to list
	_menuItems.push_back(backButton4);
	_menuItems.push_back(infModeButton);
	_menuItems.push_back(arcModeButton);
	_menuItems.push_back(normModeButton);
	
	// Draw and display window
	window.draw(sprite);
	window.display();
	
	return Menu::GetMenuResponse(window);
}

