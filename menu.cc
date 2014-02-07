
#include "menu.hh"

/* Descr: Determination about response on mouse click 
** Param: X and Y coordinates of mouse click
** Retval: response (action) on mouse click  */
Menu::MenuResult Menu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( x > menuItemRect.left
			&& x < menuItemRect.left + menuItemRect.width
			&& y > menuItemRect.top  
			&& y < menuItemRect.height + menuItemRect.top)
{
    return (*it).action;
}
	}

	return Nothing;
}

/* Function: Determination about response on users event
** Input: window
** Output: response (action) on users event  */
Menu::MenuResult Menu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{

		while(window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::MouseButtonPressed)
			{
				Menu::MenuResult clickResult = HandleClick 
                                                  (menuEvent.mouseButton.x,menuEvent.mouseButton.y);			   					if(clickResult!=Nothing) return clickResult; 
			}
			if(menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}


}
