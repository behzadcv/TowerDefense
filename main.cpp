#include "SFML/Graphics.hpp"
#include <iostream>











#include "ui.hh"
#include "tower.hh"
int main()
{

	//enum ObjectType;

	const ObjectType tow_type = ObjectType::Tow;
   	const std::string tow_desc = "This Magic Tower is the best tower in the world!";
	const float cost = 100;
	const float range = 25;
	const float damage = 50;
	const float level = 0; 
	const float slows = 25;   	
	//sf::Vector2f new_Pos(100,100);
	std::pair<int, int> tow_tile_loc(1, 1);
	TowerA newTower(tow_type, tow_desc, tow_tile_loc, cost, range, damage, level, slows);


	window.setFramerateLimit(60);
	if(!loadTextures()){// loading textures
		std::cout<<"error in loading phase";
		return 0;
	}
    sf::Vector2i newPos(0,0);
	GameGroundUI groundPlay;
	

	
	sf::Clock clock; // starts the clock
	
	 TileUI mytile;
	
    while (window.isOpen())
    {
 		window.clear();
		groundPlay.drawbackground(0);
		//sf::Time elapsed1 = clock.getElapsedTime();
		
		//sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window

		sf::Event event;/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
				//std::cout<<   localPosition.x<<"  "<<localPosition.y<<std::endl;   
				//tower_a1.drawAtPosition(localPosition);
				//placed=true;  
				//sf::Vector2i newPos2=localPosition;
		}
*/
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       
			
		std::pair<int, int> p1(0,0);
		mytile.tileDraw(p1, path,horizontal);
		
		p1.first++;
		mytile.tileDraw(p1, path,leftToDown);
		p1.second++;
		mytile.tileDraw(p1, path,vertical);
		p1.second++;
		mytile.tileDraw(p1, path,rightToTop);
		p1.first++;
		mytile.tileDraw(p1, path,horizontal);
		p1.first++;
		mytile.tileDraw(p1, path,leftToTop);
		p1.second--;
		mytile.tileDraw(p1, path,rightToDown);
		p1.first++;
		mytile.tileDraw(p1, path,horizontal);
		
		newTower.update();	

        window.display();
    }

    return 0;
}
