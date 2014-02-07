
#include "intro.hh"
#include "menu.hh"

/* Descr: Displaying preamble window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult Intro::Show(sf::RenderWindow & renderWindow)
{

	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("src/images/intro.png");
	sf::Sprite sprite;
	sprite.setTexture(image);
	
	// Draw and display window
	renderWindow.draw(sprite);
	renderWindow.display();
	
	return GetMenuResponse(renderWindow);
}

/* Descr: Determination about response on users event
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult Intro::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	// Infinite loop
	while(true)
	{
		// Responce on users event
		while(window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return ToMenu;
			}
			if(menuEvent.type == sf::Event::KeyPressed)
			{
				return ToMenu;
			}
			if(menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}

