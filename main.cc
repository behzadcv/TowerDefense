#include "game.hh"
#include "exception.hh"
#include <iostream>
#include <string>
#include <vector>
//#include "soundsys.hh"

sf::RenderWindow window(sf::VideoMode(1024, 768), "Tower Defence!");
bool isPlay=true;
/* Desrc: Display main menu window and waiting for response from user and executing it
** Param: Nothing
** Retval: Nothing  */


void MenueM::ShowMenu()
{
	MainMenu menu;
	Menu::MenuResult result = menu.Show(window);
	switch(result)
	{
	case Menu::Exit:
			isPlay=false;
			window.close();
			break;
	case Menu::Help:
			ShowHelpMenu();
			break;
	case Menu::HighScores:
			ShowHighScoresMenu();
			break;
	case Menu::GameModeMenu:
			ShowGameModeMenu();
			break;
	default: ShowMenu();
	}
}

/* Desrc: Display help window and waiting for response from user  and executing it
** Param: Nothing
** Retval: Nothing  */
void MenueM::ShowHelpMenu()
{
	HelpMenu helpMenu;

	Menu::MenuResult result = helpMenu.Show(window);
	switch(result)
	{
	case Menu::ToMenu:
			ShowMenu();
			break;
	case Menu::Exit:
			isPlay=false;
			window.close();
			break;
	default: ShowHelpMenu();
	}
}

/* Desrc: Display highscores window and waiting for response from user and executing it
** Param: Nothing
** Retval: Nothing  */
void MenueM::ShowHighScoresMenu()
{
	HighScoresMenu highScoresMenu;

	Menu::MenuResult result = highScoresMenu.Show(window);
	switch(result)
	{
	case Menu::ToMenu:
			ShowMenu();
			break;
	case Menu::Exit:
			isPlay=false;
			window.close();
			break;
	default: ShowHighScoresMenu();
	}
}

/* Desrc: Display start game menu window and waiting for response from user and executing it
** Param: Nothing
** Retval: Nothing  */
void MenueM::ShowGameModeMenu()
{
	GameModeMenu gameModeMenu;

	Menu::MenuResult result = gameModeMenu.Show(window);
	switch(result)
	{
	case Menu::ToMenu:
			ShowMenu();
			break;
	case Menu::PlayInf:
			this->gameMode=0;
			return;
			break;
	case Menu::PlayArc:
			this->gameMode=1;
			return;
			break;
	case Menu::PlayNorm:
			this->gameMode=2;
			return;
			break;
	case Menu::Exit:
			isPlay=false;
			window.close();
			break;
	default:  ShowGameModeMenu();
	}
}

/* Desrc: Display pause menu window and waiting for response from user  and executing it
** Param: Nothing
** Retval: Nothing  */
bool MenueM::ShowGameMenu()
{
	GameMenu gameMenu;
	Menu::MenuResult result = gameMenu.Show(window);
	switch(result)
	{
	case Menu::ToMenu:

			// add something for end of game
			//ShowMenu();
			return true;
			break;
	case Menu::Continue:
			//For every monster call function monster->paused(frametime + clock1.getElapsedTime().asSeconds());
			return false;
			break;
	case Menu::Exit:
			isPlay=false;
			window.close();
			break;
	default:
			ShowGameMenu();
	}
	return false;
}

/* Desrc: Saving new high score into file
** Param: name - name of player, score - reached score of player
** Retval: Nothing  */
void Game::saveHighScore(std::string name,float score)
{
	if(name == "")name = "-";
	std::string file; // file for saving highscore

	// choice of file depending on game mode
	switch(this->gameMode)
	{
	case 0:
			file="src/highscores_inf.txt";
			break;
	case 1:
			file="src/highscores_arc.txt";
			break;
	default:
			file="src/highscores_norm.txt";
			break;
	}

	std::ifstream in(file);
	std::stringstream buffer;
   	buffer << in.rdbuf(); // loading file into stream
	//std::string test = buffer.str(); // convert stream into string

	//size_t pos1 = 0; // cursors for searching in string
  	//size_t pos2;
	//td::string all[20]; // pole of strings to save all high scores and names
	//float scores[10] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};    // pole of strings to save all high scores
	//std::string names[10]; // pole of strings for save all names
	std::vector<float> scores;
	std::vector<std::string> names;

	for (int x=0; x < 10/*x<=19*/; x++){
      	  float scr = 0.0;
      	  std::string nam = std::string("anonymous");
		if(buffer.eof()){
			scores.push_back(scr);
			names.push_back(nam);
			continue;
		}
      	  buffer >> std::skipws >> scr >> nam;
      	  scores.push_back(scr);
      	  names.push_back(nam);

      	  std::cout<< scr << " "<< nam <<std::endl;


      	  //pos2 = test.find("\n", pos1); //search for the bar "\n". pos2 will be where the bar was found.
       	  //all[x] = test.substr(pos1, (pos2-pos1)); //make a substring - copy of a fragment of the big string
       	  //pos1 = pos2+1; // sets pos1 to the next character after pos2.

	  //if(x%2==0) scores[x/2]=std::stof(all[x]);
	  //if(x%2==1) names[(x-1)/2]=all[x];
        }

	std::stringstream scorestream;
	float testScore;
	std::string testName;
	int k=0;

	// make new highscore list if new score is higher than actual score
	while(k<10){
		if(score > scores[k])
		{
			std::cout<< scores[k] << " "<< names[k] << " "<< score << " "<<std::endl;
			testScore=scores[k];
			testName=names[k];
			scores[k]=score;
			names[k]=name;
			score=testScore;
			name=testName;
		}
		k++;
	}

	// input new highscores into stream
	/*for (int x=0; x<=19; x++)
      	{
       	  if(x%2==0) scorestream << scores[x/2] << std::endl;
	  if(x%2==1) scorestream << names[(x-1)/2] << std::endl;
        }*/
	for( unsigned int i = 0; i < 10; i++ ){
		std::cout << scores.at(i) << " " << names.at(i)<<std::endl;
		scorestream << scores.at(i)<<std::endl<<names.at(i)<<std::endl;
	}

	// save new highscores into file
	std::ofstream myfile;
 	myfile.open (file);
  	myfile << scorestream.str();
  	myfile.close();
  	in.close();

}


int main()
{
	MenueM menu;
	menu.ShowIntro();
	while(isPlay){
		//try{
		Game newgame;
		newgame.gameMode=menu.gameMode;

		if( newgame.gameMode == 0 ){
			newgame.playInfinity();
		}else if( newgame.gameMode == 1 ){
			newgame.playArcade();
		}else{
			newgame.playNormal();
		}
		if (!isPlay)
			return 0;
		menu.ShowHighScoresMenu();
		/*}catch( MapReadError maperr ){
			std::cout << maperr.reason() << std::endl;
		}catch( RuntimeError rerr ){
			std::cout << rerr.reason() << std::endl;
		}catch(...){
			std::cout << "Unregocnized error occured." << std::endl;
		}*/
	}
    	return 0;
}
/* Desrc: Display preamble window and waiting for response from user and executing it
** Param: Nothing
** Retval: Nothing  */
void MenueM::ShowIntro()
{
	Intro intro;
	Menu::MenuResult result = intro.Show(window);
	if(result == Menu::ToMenu){
		ShowMenu();
	}
	if(result == Menu::Exit){
			isPlay=false;
			window.close();
	}
}

