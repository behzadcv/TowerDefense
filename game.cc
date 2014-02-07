#include "game.hh"
#include "tdmap.hh"
#include "wave.hh"
#include "menu.hh"
#include "mainMenu.hh"
#include "helpMenu.hh"
#include "highScoresMenu.hh"
#include "gameModeMenu.hh"
#include "intro.hh"
#include "monsters.hh"
#include "soundsys.hh"

std::pair<int, int> detectTileIndex(sf::Vector2i currPos){

    int X=int((currPos.x)/85.0 );
    int Y=int((currPos.y-40)/85.0 );

    std::pair<int, int> ret(X,Y);
    return ret;
}


/* Implementation of game.hh. The game loop is here that goes until final conditions are met.
 */

	void Game::playInfinity()	{
		//sound snd1("src/sounds/test.wav");		//it's a beginning anyways
		//snd1.play();

		window.setFramerateLimit(60);
		if(!loadTextures()){// loading textures
			std::cout<<"error in loading phase";
			return;
		}

		GameGroundUI generalUI;

        tdMap testMap1("src/infinity");

		infinityWaves infinity(&newplayer);

        infinity.deploy(clock.getElapsedTime().asSeconds());

        DragAndDrop dragAndDrop;
        	//sf::Clock clock; // starts the clock
		MenueM menu;

		std::string name=getName();

	    while (window.isOpen())
	    {


			//sf::Time dt = clock.restart();
			window.clear();
			generalUI.drawbackground(0);
			generalUI.UIShowError(clock.getElapsedTime().asSeconds());
			testMap1.draw();
			sf::Event event;
			std::pair<int, int> miniMenuDetectedTile;
			while (window.pollEvent(event))
			{

				switch (event.type)
   				{
					case sf::Event::Closed:{
						window.close();
						isPlay=false;
						break;
					}

					case sf::Event::MouseButtonPressed:{

					sf::Vector2i mouseClickXY;


					if (isDrag==towerSelected)
						{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerA){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(1),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerB){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(2),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerC){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(0),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (firstShootTL,firstShootDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****firstShoot******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(3),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
							break;
							}

							if(dragAndDrop.isRange (fastestTL,fastestDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****fastest******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(5),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (mostHealthTL,mostHealthDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****mostHealth******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(4),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
						}

						if (event.mouseButton.button == sf::Mouse::Left && isDrag==invalidTile)   /*invalidTile 1st detect click*/
							{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							isDrag=dragAndDrop.detectTileType(mouseClickXY);
							if (isDrag==buyLivs){/*on buy live clicked*/
								isDrag=invalidTile;
								generalUI.UISetError(newplayer.buyLive(),clock.getElapsedTime().asSeconds());
								break;
							}
							if (isDrag==towerRange) /*tower is selected*/
								{
								miniMenuDetectedTile=detectTileIndex(mouseClickXY);
								std::cout<<"in range"<<std::endl;
								if(newplayer.selectTower(miniMenuDetectedTile))
									{
									std::cout<<"tower is found"<<std::endl;
									isDrag=towerSelected;
									break;
									}
								}

							}

							/*game menue is selected*/
							if( event.mouseButton.x > 921 && event.mouseButton.x < 1011 &&
								event.mouseButton.y > 26 && event.mouseButton.y < 114)
							{
								float time_of_pause = clock.getElapsedTime().asSeconds();
								if(menu.ShowGameMenu()){
		saveHighScore(name, newplayer.getScoreF());
 return;}
								//if () return;
								infinity.getCurrentWave().paused(clock.getElapsedTime().asSeconds());
								newplayer.paused(time_of_pause, clock.getElapsedTime().asSeconds());
							}
								break;
							}
						case sf::Event::KeyPressed:{
							if (event.key.code == sf::Keyboard::Escape)
	   						{
		    						menu.ShowGameMenu();
								}
						break;
						}

							/*after selecting a tower to buy realse the mouse botton*/
						case sf::Event::MouseButtonReleased:{
							sf::Vector2i mouseClickXY(event.mouseButton.x,event.mouseButton.y);
				           if(isDrag!=towerSelected){

							 if(isDrag!=towerRange && isDrag!=invalidTile && detectTileIndex(mouseClickXY).first<10 && detectTileIndex(mouseClickXY).second<8 && testMap1.getTileTypes(detectTileIndex(mouseClickXY).first,detectTileIndex(mouseClickXY).second).first==terrain::ground)
										{

											generalUI.UISetError(newplayer.buyTower(isDrag,detectTileIndex(mouseClickXY), infinity),clock.getElapsedTime().asSeconds());

													 isDrag=invalidTile;
													break;
				                		}else {
										if(isDrag!=invalidTile) generalUI.UISetError("Wrong Place",clock.getElapsedTime().asSeconds());
										isDrag=invalidTile;
								}

							}
				                		break;
						}
						default:
								break;
						}

				}//window event


		        UItext(15,"-$100",977,717,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$150",973,617,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$350",973,507,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$500",973,396,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"-$1000",940,195,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(20,"SCORE: " +newplayer.getScore(),560,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"MONEY: $ "+newplayer.getMoney(),360,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"LIVES: " +newplayer.getLivesS(),760,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"WAVE: -inf" ,870,5,sf::Text::Bold,sf::Color(255,255,255));
				std::list<Tower*> towers = newplayer.getTowersList();

				for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
					//std::cout << (*iter)->getLevel() << std::endl;
					// (*iter)->upgrade();
					(*iter)->update(clock.getElapsedTime().asSeconds());
				}
				//updating monsters
				infinity.update( clock.getElapsedTime().asSeconds(), testMap1 );
				//newboss.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflying.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflyer.update(clock.getElapsedTime().asSeconds(), testMap1);
				//deploying monsters

				generalUI.drawMoon();
				UItext(20,"Dear "+name+" Welcome!",10,30,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(25,"Galaxy Tower Defence",10,1,sf::Text::Bold,sf::Color(255,255,255));
				generalUI.drawCloud(0);
				generalUI.drawCloud(1);
				dragAndDrop.dragTower();
				window.display();
				/*if(clock.getElapsedTime().asSeconds() > 15)	{
					newplayer.getLives() = 0;
				} */
				if( newplayer.getLives() == 0){break;}
	    	}

		newplayer.giveScore(newplayer.getMoneyF());
		saveHighScore(name, newplayer.getScoreF());

	}

//*********************************************************************************************************************infinity********************************************************************'

//*********************************************************************************************************************arcade***********************************************************************'

void Game::playArcade()	{
		//sound snd1("src/sounds/test.wav");		//it's a beginning anyways
		//snd1.play();

		window.setFramerateLimit(60);
		if(!loadTextures()){// loading textures
			std::cout<<"error in loading phase";
			return;
		}

		GameGroundUI generalUI;

        tdMap testMap1("src/arcade");

		arcadeWaves arcade(&newplayer);



        DragAndDrop dragAndDrop;
        	//sf::Clock clock; // starts the clock
		MenueM menu;

		std::string name=getName();

	    while (window.isOpen())
	    {

			arcade.deploy(clock.getElapsedTime().asSeconds());
			//sf::Time dt = clock.restart();
			window.clear();
			generalUI.drawbackground(0);
			generalUI.UIShowError(clock.getElapsedTime().asSeconds());
			testMap1.draw();
			sf::Event event;
			std::pair<int, int> miniMenuDetectedTile;
			while (window.pollEvent(event))
			{

				switch (event.type)
   				{
					case sf::Event::Closed:{
						window.close();
						isPlay=false;
						break;
					}

					case sf::Event::MouseButtonPressed:{

					sf::Vector2i mouseClickXY;


					if (isDrag==towerSelected)
						{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerA){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(1),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerB){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(2),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerC){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(0),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (firstShootTL,firstShootDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****firstShoot******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(3),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
							break;
							}

							if(dragAndDrop.isRange (fastestTL,fastestDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****fastest******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(5),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (mostHealthTL,mostHealthDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****mostHealth******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(4),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
						}

						if (event.mouseButton.button == sf::Mouse::Left && isDrag==invalidTile)   /*invalidTile 1st detect click*/
							{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							isDrag=dragAndDrop.detectTileType(mouseClickXY);
							if (isDrag==buyLivs){/*on buy live clicked*/
								isDrag=invalidTile;
								generalUI.UISetError(newplayer.buyLive(),clock.getElapsedTime().asSeconds());
								break;
							}
							if (isDrag==towerRange) /*tower is selected*/
								{
								miniMenuDetectedTile=detectTileIndex(mouseClickXY);
								std::cout<<"in range"<<std::endl;
								if(newplayer.selectTower(miniMenuDetectedTile))
									{
									std::cout<<"tower is found"<<std::endl;
									isDrag=towerSelected;
									break;
									}
								}

							}

							/*game menue is selected*/
							if( event.mouseButton.x > 921 && event.mouseButton.x < 1011 &&
								event.mouseButton.y > 26 && event.mouseButton.y < 114)
							{
								float time_of_pause = clock.getElapsedTime().asSeconds();
								if(menu.ShowGameMenu()){
		saveHighScore(name, newplayer.getScoreF());
 return;}
								//if () return;
								arcade.getCurrentWave().paused(clock.getElapsedTime().asSeconds());
								newplayer.paused(time_of_pause, clock.getElapsedTime().asSeconds());
							}
								break;
							}
						case sf::Event::KeyPressed:{
							if (event.key.code == sf::Keyboard::Escape)
	   						{
		    						menu.ShowGameMenu();
								}
						break;
						}

							/*after selecting a tower to buy realse the mouse botton*/
						case sf::Event::MouseButtonReleased:{
							sf::Vector2i mouseClickXY(event.mouseButton.x,event.mouseButton.y);
				           if(isDrag!=towerSelected){

							 if(isDrag!=towerRange && isDrag!=invalidTile && detectTileIndex(mouseClickXY).first<10 && detectTileIndex(mouseClickXY).second<8 && testMap1.getTileTypes(detectTileIndex(mouseClickXY).first,detectTileIndex(mouseClickXY).second).first==terrain::ground)
										{

											generalUI.UISetError(newplayer.buyTower(isDrag,detectTileIndex(mouseClickXY), arcade),clock.getElapsedTime().asSeconds());

													 isDrag=invalidTile;
													break;
				                		}else {
										if(isDrag!=invalidTile) generalUI.UISetError("Wrong Place",clock.getElapsedTime().asSeconds());
										isDrag=invalidTile;
								}

							}
				                		break;
						}
						default:
								break;
						}

				}//window event


		        UItext(15,"-$100",977,717,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$150",973,617,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$350",973,507,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$500",973,396,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"-$1000",940,195,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(20,"SCORE: " +newplayer.getScore(),560,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"MONEY: $ "+newplayer.getMoney(),360,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"LIVES: " +newplayer.getLivesS(),760,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"WAVE: " +arcade.getWaveNumber(),870,5,sf::Text::Bold,sf::Color(255,255,255));
				std::list<Tower*> towers = newplayer.getTowersList();

				for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
					//std::cout << (*iter)->getLevel() << std::endl;
					// (*iter)->upgrade();
					(*iter)->update(clock.getElapsedTime().asSeconds());
				}
				//updating monsters
				arcade.update( clock.getElapsedTime().asSeconds(), testMap1 );
				//newboss.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflying.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflyer.update(clock.getElapsedTime().asSeconds(), testMap1);
				//deploying monsters

				generalUI.drawMoon();
				UItext(20,"Dear "+name+" Welcome!",10,30,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(25,"Galaxy Tower Defence",10,1,sf::Text::Bold,sf::Color(255,255,255));
				generalUI.drawCloud(0);
				generalUI.drawCloud(1);
				dragAndDrop.dragTower();
				window.display();
				/*if(clock.getElapsedTime().asSeconds() > 15)	{
					newplayer.getLives() = 0;
				} */
				if( newplayer.getLives() == 0){break;}
	    	}

		newplayer.giveScore(newplayer.getMoneyF());
		saveHighScore(name, newplayer.getScoreF());

	}


//**********************************************************************************************************************************arcade******************************************************************'''

//*******************************************************************************************************************************normal********************************************************************''

void Game::playNormal()	{
		//sound snd1("src/sounds/test.wav");		//it's a beginning anyways
		//snd1.play();

		window.setFramerateLimit(60);
		if(!loadTextures()){// loading textures
			std::cout<<"error in loading phase";
			return;
		}

		GameGroundUI generalUI;

        tdMap testMap1("src/normal");

		normalWaves normal(&newplayer);

        //normal.deploy(clock.getElapsedTime().asSeconds());

        DragAndDrop dragAndDrop;
        	//sf::Clock clock; // starts the clock
		MenueM menu;

		std::string name=getName();

	    while (window.isOpen() && normal.getWaveNumber() != "51")
	    {

			normal.deploy(clock.getElapsedTime().asSeconds());
			//sf::Time dt = clock.restart();
			window.clear();
			generalUI.drawbackground(0);
			generalUI.UIShowError(clock.getElapsedTime().asSeconds());
			testMap1.draw();
			sf::Event event;
			std::pair<int, int> miniMenuDetectedTile;
			while (window.pollEvent(event))
			{

				switch (event.type)
   				{
					case sf::Event::Closed:{
						window.close();
						isPlay=false;
						break;
					}

					case sf::Event::MouseButtonPressed:{

					sf::Vector2i mouseClickXY;


					if (isDrag==towerSelected)
						{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerA){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(1),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerB){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(2),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.detectTileType(mouseClickXY)==buyTowerC){//detect correct upgrade sell or cancel
								std::cout<<"*****Detect upgrade sell or cancel******"<<std::endl;
									generalUI.UISetError(newplayer.whichAction(0),clock.getElapsedTime().asSeconds());
									isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (firstShootTL,firstShootDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****firstShoot******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(3),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
							break;
							}

							if(dragAndDrop.isRange (fastestTL,fastestDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****fastest******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(5),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}

							if(dragAndDrop.isRange (mostHealthTL,mostHealthDR,mouseClickXY)){//detect correct upgrade sell or cancel
								std::cout<<"*****mostHealth******"<<std::endl;
								generalUI.UISetError(newplayer.whichAction(4),clock.getElapsedTime().asSeconds());
								isDrag=invalidTile;
								break;
							}
						}

						if (event.mouseButton.button == sf::Mouse::Left && isDrag==invalidTile)   /*invalidTile 1st detect click*/
							{
							mouseClickXY.x=event.mouseButton.x;
							mouseClickXY.y=event.mouseButton.y;
							isDrag=dragAndDrop.detectTileType(mouseClickXY);
							if (isDrag==buyLivs){/*on buy live clicked*/
								isDrag=invalidTile;
								generalUI.UISetError(newplayer.buyLive(),clock.getElapsedTime().asSeconds());
								break;
							}
							if (isDrag==towerRange) /*tower is selected*/
								{
								miniMenuDetectedTile=detectTileIndex(mouseClickXY);
								std::cout<<"in range"<<std::endl;
								if(newplayer.selectTower(miniMenuDetectedTile))
									{
									std::cout<<"tower is found"<<std::endl;
									isDrag=towerSelected;
									break;
									}
								}

							}

							/*game menue is selected*/
							if( event.mouseButton.x > 921 && event.mouseButton.x < 1011 &&
								event.mouseButton.y > 26 && event.mouseButton.y < 114)
							{
								float time_of_pause = clock.getElapsedTime().asSeconds();
								if(menu.ShowGameMenu()){
		saveHighScore(name, newplayer.getScoreF());
 return;}
								//if () return;
								normal.getCurrentWave().paused(clock.getElapsedTime().asSeconds());
								newplayer.paused(time_of_pause, clock.getElapsedTime().asSeconds());
							}
								break;
							}
						case sf::Event::KeyPressed:{
							if (event.key.code == sf::Keyboard::Escape)
	   						{
		    						menu.ShowGameMenu();
								}
						break;
						}

							/*after selecting a tower to buy realse the mouse botton*/
						case sf::Event::MouseButtonReleased:{
							sf::Vector2i mouseClickXY(event.mouseButton.x,event.mouseButton.y);
				           if(isDrag!=towerSelected){

							 if(isDrag!=towerRange && isDrag!=invalidTile && detectTileIndex(mouseClickXY).first<10 && detectTileIndex(mouseClickXY).second<8 && testMap1.getTileTypes(detectTileIndex(mouseClickXY).first,detectTileIndex(mouseClickXY).second).first==terrain::ground)
										{

											generalUI.UISetError(newplayer.buyTower(isDrag,detectTileIndex(mouseClickXY), normal),clock.getElapsedTime().asSeconds());

													 isDrag=invalidTile;
													break;
				                		}else {
										if(isDrag!=invalidTile) generalUI.UISetError("Wrong Place",clock.getElapsedTime().asSeconds());
										isDrag=invalidTile;
								}

							}
				                		break;
						}
						default:
								break;
						}

				}//window event


		        UItext(15,"-$100",977,717,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$150",973,617,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$350",973,507,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(15,"-$500",973,396,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"-$1000",940,195,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(20,"SCORE: " +newplayer.getScore(),560,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"MONEY: $ "+newplayer.getMoney(),360,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"LIVES: " +newplayer.getLivesS(),760,5,sf::Text::Bold,sf::Color(255,255,255));
				UItext(20,"WAVE: " +normal.getWaveNumber()+"/50",870,5,sf::Text::Bold,sf::Color(255,255,255));
				std::list<Tower*> towers = newplayer.getTowersList();

				for(auto iter = towers.begin(); iter != towers.end(); iter++)	{
					//std::cout << (*iter)->getLevel() << std::endl;
					// (*iter)->upgrade();
					(*iter)->update(clock.getElapsedTime().asSeconds());
				}
				//updating monsters
				normal.update( clock.getElapsedTime().asSeconds(), testMap1 );
				//newboss.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflying.update(clock.getElapsedTime().asSeconds(), testMap1);
				//newflyer.update(clock.getElapsedTime().asSeconds(), testMap1);
				//deploying monsters

				generalUI.drawMoon();
				UItext(20,"Dear "+name+" Welcome!",10,30,sf::Text::Bold,sf::Color(255,255,255));
		        UItext(25,"Galaxy Tower Defence",10,1,sf::Text::Bold,sf::Color(255,255,255));
				generalUI.drawCloud(0);
				generalUI.drawCloud(1);
				dragAndDrop.dragTower();
				window.display();
				/*if(clock.getElapsedTime().asSeconds() > 15)	{
					newplayer.getLives() = 0;
				} */
				if( newplayer.getLives() == 0){break;}
	    	}

		newplayer.giveScore(newplayer.getMoneyF());
		saveHighScore(name, newplayer.getScoreF());

	}

//**************************************************************************************************************************************************************normal**************************************************



std::string getName(){
		std::string str="";
		size_t charCounter=0;
		while (window.isOpen())
	    	{
			window.clear();
			GameGroundUI generalUI;
			generalUI.drawbackground(1);
			sf::Event event;
				while (window.pollEvent(event))
					{
					switch (event.type)
   						{
						case sf::Event::Closed:
							isPlay=false;
			    			window.close();
			    			break;
						case sf::Event::TextEntered:
						{
  							  if (event.text.unicode ==13){
								return (str);
								}
							  if (event.text.unicode ==8){
									if (str.size () > 0){  str.resize (str.size () - 1);
									charCounter--;}
									break;
							  }
							if (event.text.unicode < 128 && charCounter<10)
								{
									str += static_cast<char>(event.text.unicode);
									charCounter++;
								}

						break;
						}
						default:
		    				break;
					}

					}
			//generalUI.drawbackground(0);
			//std::string name;
			//std::cout << "Please enter your name" << std::endl;
			//std::cin >> name;
			 UItext(35,"Your name is: "+str,330,360,sf::Text::Bold,sf::Color(255,255,255));
			window.display();
			}
		return str;
}





