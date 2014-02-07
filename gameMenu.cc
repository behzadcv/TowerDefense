
#include "gameMenu.hh"
#include "menu.hh"

/* Descr: Displaying pause menu window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult GameMenu::Show(sf::RenderWindow & window)
{

	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("src/images/gamemenu.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	//load list of highscores and names and display them

	// Setup clickable regions

	// "Menu" button coordinates
	MenuItem menuButton;
	menuButton.rect.top= 200;
	menuButton.rect.height = 350;
	menuButton.rect.left = 200;
	menuButton.rect.width = 320;
	menuButton.action = ToMenu;

	// "Continue" button coordinates
	MenuItem continueButton;
	continueButton.rect.top= 200;
	continueButton.rect.height = 350;
	continueButton.rect.left = 521;
	continueButton.rect.width = 320;
	continueButton.action = Continue;
	
	// Putting new items to list
	_menuItems.push_back(menuButton);
	_menuItems.push_back(continueButton);
	
	// Draw and display window
	window.draw(sprite);
	window.display();

	return Menu::GetMenuResponse(window);
}

