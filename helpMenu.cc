
#include "helpMenu.hh"
#include "menu.hh"

/* Descr: Displaying help menu window
** Input: Window
** Output: Response (action) on users event  */
Menu::MenuResult HelpMenu::Show(sf::RenderWindow& window)
{

	// Load menu image from file
	sf::Texture image;
	image.loadFromFile("src/images/helpmenu.png");
	sf::Sprite sprite;
	sprite.setTexture(image);

	// "Back" button coordinates
	MenuItem backButton;
	backButton.rect.top= 60;
	backButton.rect.height = 80;
	backButton.rect.left = 18;
	backButton.rect.width = 112;
	backButton.action = ToMenu;

	// Putting new item to list
	_menuItems.push_back(backButton);
	
	// Load font from file
	sf::Font font;
	font.loadFromFile("src/images/JennaSue.ttf");
	
	// Text inicialization
	sf::Text text("Game description", font, 40);
	text.setStyle(sf::Text::Bold);
	text.setPosition(90.f, 240.f);
	

	sf::Text text1("Tower defence is a single player game in which the player place"
		      "towers alongside a given road in order to prevent\n"
		      "waves of monsters from passing through road. The player starts"
		      "with a given number of lives and money. The money\n"
		      "can be used for purchasing towers and upgrading them or for buying"
                      "more lives. Towers can be sold.\n", font, 30);
	text1.setPosition(90.f, 280.f);
	

	sf::Text text2("Game modes", font, 40);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(90.f, 380.f);
	

	sf::Text text3("Infinity mode - there is one infinitely large wave, player tries"
                       "to survive as long as possible and get the highest score\n"
		       "Arcade mode - there is infinite number of waves and goal"
                       "is to survive as long as possible and get highest score\n"
		       "Normal mode - there is fixed number of waves, goal is to complete"
                       "all waves and get the highest score.\n", font, 30);
	text3.setPosition(90.f, 420.f);

	sf::Text text4("Towers", font, 40);
	text4.setStyle(sf::Text::Bold);
	text4.setPosition(90.f, 520.f);

	sf::Text text5("Fire Tower - Very fast air shooting tower with freezing ability, light damage & big range! Best for early stages!\n"
			"Ice Tower - Fast ground shooting tower, light damage with a slowing ability and good range!\n"
			"Magic Tower - Rather slow air shooting tower with both freezing and slowing abilities. Good damage!\n"
		       "Hard Defence - The slowest of all towers. Has splash damage and can reverse monsters. Very high damage!\n", font, 30);
	text5.setPosition(90.f, 560.f);

	// Draw and display text and window
	window.draw(sprite);
	window.draw(text);
	window.draw(text1);
	window.draw(text2);
	window.draw(text3);
	window.draw(text4);
	window.draw(text5);
	window.display();
	
	return Menu::GetMenuResponse(window);
}

