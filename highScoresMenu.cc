
#include "highScoresMenu.hh"
#include "menu.hh"

/* Descr: Displaying High scores menu window
** Param: Window
** Retval: Response (action) on users event  */
Menu::MenuResult HighScoresMenu::Show(sf::RenderWindow& window)
{

	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("src/images/highscoresmenu.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	// Load font from file
	sf::Font font;
	font.loadFromFile("src/images/JennaSue.ttf");
	
	// Text inicialization
	sf::Text text("Arcade mode", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setPosition(90.f, 250.f);

	// Text1 inicialization
	sf::Text text1("Normal mode", font, 40);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(385.f, 250.f);

	// Text2 inicialization
	sf::Text text2("Infinity mode", font, 40);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(700.f, 250.f);

	// Draw texts	
	window.draw(sprite);
	window.draw(text);
	window.draw(text1);
	window.draw(text2);

	// Inicialization of strigs for saving names and highscores
	std::string score_arc;
	std::string name_arc;
	std::string score_norm;
	std::string name_norm;
	std::string score_inf;
	std::string name_inf;
	
	//load the text files and put it into a single strings
	std::ifstream inArc("src/highscores_arc.txt");
   	std::ifstream inNorm("src/highscores_norm.txt");
	std::ifstream inInf("src/highscores_inf.txt");
    	std::stringstream bufferArc;
   	bufferArc << inArc.rdbuf();
	std::stringstream bufferNorm;
   	bufferNorm << inNorm.rdbuf();
	std::stringstream bufferInf;
   	bufferInf << inInf.rdbuf();
   	std::string testArc = bufferArc.str();
	std::string testNorm = bufferNorm.str();
	std::string testInf = bufferInf.str();
	   	
	//create variables that will act as "cursors"
    	size_t pos1 = 0;
  	size_t pos2;
	size_t pos3 = 0;
  	size_t pos4;
    	size_t pos5 = 0;
  	size_t pos6;

   	//create the arrays to store the strings.
        std::string rowArc[20];
	std::string rowNorm[20];
	std::string rowInf[20];
	
	
   	for (int x=0; x<=19; x++){
      	  pos2 = testArc.find("\n", pos1); //search for the bar "\n". pos2 will be where the bar was found.
       	  rowArc[x] = testArc.substr(pos1, (pos2-pos1)); //make a substring - copy of a fragment of the big string
       	  pos1 = pos2+1; // sets pos1 to the next character after pos2. 
	
	  pos4 = testNorm.find("\n", pos3); // the same for Normal mode highscores string
       	  rowNorm[x] = testNorm.substr(pos3, (pos4-pos3));  
       	  pos3 = pos4+1;

	  pos6 = testInf.find("\n", pos5);  // the same for Infinity mode highscores string
       	  rowInf[x] = testInf.substr(pos5, (pos6-pos5));  
       	  pos5 = pos6+1;
        }

	//load list of highscores and names and display them
	std::stringstream scoreArc;
	std::stringstream nameArc;
	std::stringstream scoreNorm;
	std::stringstream nameNorm;
	std::stringstream scoreInf;
	std::stringstream nameInf;

	// devide highscores and names into two streams 
	for (int i=0; i<20; i++){
      	  	if(i%2==0)
		{
			scoreArc << rowArc[i] << std::endl;
			scoreNorm << rowNorm[i] << std::endl;
			scoreInf << rowInf[i] << std::endl;
		}
		else
		{
			nameArc << rowArc[i] << std::endl;
			nameNorm << rowNorm[i] << std::endl;
			nameInf << rowInf[i] << std::endl;
		}
        }

	// put streams into strings
	score_arc=scoreArc.str();
	name_arc=nameArc.str();
	score_norm=scoreNorm.str();
	name_norm=nameNorm.str();
	score_inf=scoreInf.str();
	name_inf=nameInf.str();
	
	// Text3 and 4 inicialization and drawing
	sf::Text text3(score_arc, font, 30);
	text3.setPosition(90.f, 290.f);
	sf::Text text4(name_arc, font, 30);
	text4.setPosition(180.f, 290.f);
	window.draw(text3);
	window.draw(text4);
	 
	// Text5 and 6 inicialization and drawing
	sf::Text text5(score_norm, font, 30);
	text5.setPosition(385.f, 290.f);
	sf::Text text6(name_norm, font, 30);
	text6.setPosition(475.f, 290.f);
	window.draw(text5);
	window.draw(text6);
	
	// Text7 and 8 inicialization and drawing
	sf::Text text7(score_inf, font, 30);
	text7.setPosition(700.f, 290.f);
	sf::Text text8(name_inf, font, 30);
	text8.setPosition(790.f, 290.f);
	window.draw(text7);
	window.draw(text8);
	 
	// "Back" button coordinates
	MenuItem backButton3;
	backButton3.rect.top= 60;
	backButton3.rect.height = 80;
	backButton3.rect.left = 18;
	backButton3.rect.width = 112;
	backButton3.action = ToMenu;
	
	// Putting new item to list
	_menuItems.push_back(backButton3);

	// display window
	window.display();

	return Menu::GetMenuResponse(window);
}
