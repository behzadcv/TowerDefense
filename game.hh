#ifndef TOWER_DEFENCE__GAME_HH
#define TOWER_DEFENCE__GAME_HH

#include "SFML/Graphics.hpp"
#include <iostream>

#include "ui.hh"
#include "object.hh"
#include "player.hh"
#include "context.hh"
#include "menu.hh"
#include "intro.hh"
#include "mainMenu.hh"
#include "helpMenu.hh"
#include "highScoresMenu.hh"
#include "gameModeMenu.hh"
#include "gameMenu.hh"
#include <string>
#include <sstream>
#include <fstream>


extern	bool isPlay;
/* This class contains everything to do with the game as a whole, not just a single
 * game. It should have the highscores for all games played stored in some txt
 * file. In the end of the game it should also store the newest highscore if it say
 * fits in the top 15.
 */
class MenueM{
	
	public:
	void ShowIntro();
	void ShowMenu();
	void ShowHelpMenu();
	void ShowHighScoresMenu();
	void ShowGameModeMenu();
	bool ShowGameMenu();
	int gameMode;

};

std::string getName();
class Game
{
public:
	Game(const int Mode = 0){
	gameMode = Mode;	
	//std::string name = "Dimitar";
	//newplayer = Player newPlayer1(name);
	}
	
	~Game(){}

	void playInfinity(void);
	void playArcade(void);
	void playNormal(void);
	/*
	//Plays a game. A map of player's name and highscore is returned in the end.
    	std::map<const Player*, size_t> play();
    	//std::pair<const Player*, sizr_t> play(); // I suggest this because I think map is bit overkill. Though I don't know what you are planning 		to do but anyways.*/


	std::string name;
	Player newplayer;
	int gameMode;
	sf::Clock clock;
	   
	void saveHighScore(std::string score, float name);

};



#endif
