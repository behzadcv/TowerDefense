#ifndef UI_HH
#define UI_HH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <sstream>

#define T_RANGE 150
extern sf::RenderWindow window;

/*textures should be global values for memory efficincy, wiil be initialized in loadTextures() function*/
extern sf::Texture back_game;// game back ground
extern sf::Texture pathUI;// corner in the path 
extern sf::Texture textureTowerA;// Tower A texture
extern sf::Texture textureTowerB;// Tower B texture
extern sf::Texture textureTowerC;// Tower C texture
extern sf::Texture textureTowerD;// Tower C texture
extern sf::Texture Textureforest;// forest texture
extern sf::Texture cloud1;
extern sf::Texture monster1;
extern sf::Texture monster2;
extern sf::Texture flymonster1;
extern sf::Texture flymonster2;
extern sf::Texture bossmonster;
extern sf::Texture bulletA;
extern sf::Texture bulletI;
extern sf::Texture rangeUI;
extern sf::Texture rangePurUI;
extern sf::Texture rangeRed;
extern sf::Texture rangeGrean;
extern sf::Texture rightSide;
extern sf::Texture moon;
extern sf::Font font;


const  sf::Vector2i gameMenuTL(645,34);
const  sf::Vector2i gameMenuDR(800,600); 

const  sf::Vector2i buyLiveTL(930,125);
const  sf::Vector2i buyLiveDR(1008,200);

const  sf::Vector2i buyTowerDTL(915,315);
const  sf::Vector2i buyTowerDDR(1010,430);
 
const  sf::Vector2i buyTowerATL(915,431);
const  sf::Vector2i buyTowerADR(1010,545);

const  sf::Vector2i buyTowerBTL(915,546);
const  sf::Vector2i buyTowerBDR(1010,660);

const  sf::Vector2i buyTowerCTL(915,661);
const  sf::Vector2i buyTowerCDR(1010,775);

const sf::Vector2i tileRangeTL(0,40);
const sf::Vector2i tileRangeDR(850,720);

const sf::Vector2i firstShootTL(910,320);
const sf::Vector2i firstShootDR(1024,340);
const sf::Vector2i fastestTL(910,340);
const sf::Vector2i fastestDR(1024,360);
const sf::Vector2i mostHealthTL(910,360);
const sf::Vector2i mostHealthDR(1024,380);

//extern bool dragingA;
//extern bool dragingB=0;
//extern bool dragingC=0;



/*
struct miniMuneItems{
    miniMuneItems( std::string tN, int r, std::string uC, std::string pS ) : towerName(tN),range(r),upgradeCost(uC), priceSell(pS){}
    miniMuneItems() : towerName("Tower Name"),range(150),upgradeCost("100"), priceSell("100"){}
	


	
    std::string towerName;

	float range;
	std::string upgradeCost;
	std::string priceSell;
};*/
class Tower ;
typedef enum {
	
	path,			//0
	ground,			//1
	forest,			//2
	swamp,			//3
	buyTowerA,		//
	buyTowerB,		//
	buyTowerC,		//
	buyTowerD,
	buyLivs,
	invalidTile,	//7
	start,
	towerRange,
	towerSelected,
	firstShoot,
	fastest,
	mostHealth,
	end				//9
}terrain;



typedef enum {
	horizontal,	//0
	vertical,	//1
	leftToTop,	//2
	rightToTop,	//3
	leftToDown,	//4
	rightToDown,	//5
	leftUpDown,	//6	
	rightUpDown,	//7
	leftRightUp,	//8
	leftRightDown,	//9
	none
}path_type;

extern terrain isDrag;


void UItext(size_t, const std::string,int,int,sf::Text::Style,sf::Color);

class userInterface : public sf::Sprite
{

public:

	userInterface() {animationParameter=0;}
	virtual ~userInterface() {};


	

protected:
	sf::Sprite symbol;
	float animationParameter;	
		

};

/*monster*/
class monsterUI : public userInterface{
	public:
		
		void drawAtPositionDirection(sf::Vector2i,float speed=0.1,int direct=1,int life=100);

	private:
	sf::RectangleShape rectangleLife;

};

class monsterAUI :  public monsterUI{
public:
			monsterAUI() {
			symbol.setTexture(monster1);				
	}
};

class monsterBUI :  public monsterUI {//userInterface{
public:
			monsterBUI() {
			symbol.setTexture(monster2);	
	}
};

class monsterFAUI :  public monsterUI{
public:
			monsterFAUI() {
			symbol.setTexture(flymonster1);				
	}
};
class monsterFBUI :  public monsterUI{
public:
			monsterFBUI() {
			symbol.setTexture(flymonster2);				
	}
};
class monsterBossUI :  public monsterUI{
public:
			monsterBossUI() {
			symbol.setTexture(bossmonster);				
	}
};
/*tower*/

class towerUI: public userInterface{
	public:
	void drawAtPositionLevel(std::pair<int, int>,float,bool miniMune=false,const std::string &nTower =std::string("Fire Power"),const std::string &sPrice =std::string("100"), const std::string &uCost =std::string("200"), float range = 300);
	void drawDragAtPosition(sf::Vector2i);
	void animationBullet(sf::Vector2f,sf::Vector2f);

protected:

	sf::Sprite rangeTowerSymbol;
	sf::Vector2f src;
	sf::Vector2f des;
	sf::Vector2f current;
	bool onFire;
	sf::Sprite bulletSymbol;
	sf::Sprite rightSideSymbol;
	int bulletPara;
};

class towerAUI : public towerUI{
public:
			towerAUI() {
			onFire=false;
			bulletSymbol.setTexture(bulletI);
			symbol.setTexture(textureTowerA);
			rangeTowerSymbol.setTexture(rangeUI);
			rightSideSymbol.setTexture(rightSide);
			
	}
			
};

class towerBUI : public towerUI{
public:
			towerBUI() {
			onFire=false;
			rangeTowerSymbol.setTexture(rangePurUI);
			bulletSymbol.setTexture(bulletA);
			symbol.setTexture(textureTowerB);
			rightSideSymbol.setTexture(rightSide);	
	}

};
class towerCUI :  public towerUI{
public:
			towerCUI(){
			onFire=false;
			bulletSymbol.setTexture(bulletA);
			symbol.setTexture(textureTowerC);
			rangeTowerSymbol.setTexture(rangeRed);
			rightSideSymbol.setTexture(rightSide);	
	}

};

class towerDUI :  public towerUI{
public:
			towerDUI(){
			onFire=false;
			bulletSymbol.setTexture(bulletI);
			symbol.setTexture(textureTowerD);
			rangeTowerSymbol.setTexture(rangeGrean);
			rightSideSymbol.setTexture(rightSide);	
	}

};




class GameGroundUI :  public userInterface{
public:
			GameGroundUI() {
			symbol.setTexture(back_game);
			cloudUI1.setTexture(cloud1);
			moonUI.setTexture(moon);
			moonUI.setPosition(0,0);
			errClock=0;
	}
		void drawAtPositionDirection(sf::Vector2i,float)=delete;

		void UIShowError(float time=0);
		void UISetError(const std::string,float);
		void drawbackground(size_t);
		void drawCloud(float);
		void drawMoon();
		//void drawMoon();
		

private:
	sf::Sprite cloudUI1;
	sf::Sprite moonUI;
	std::string errMsg;
	float errClock;

};






class TileUI :  public userInterface{
public:
		TileUI() {}
		void tileDraw(std::pair<int, int>, terrain,path_type);
		void drawAtPositionDirection(sf::Vector2i,float)=delete;
private:
		terrain te;
		path_type pType;
};



class DragAndDrop{
	public:
		DragAndDrop(){}
		terrain detectTileType(sf::Vector2i);
		terrain dragTower();


		bool isRange(sf::Vector2i,sf::Vector2i,sf::Vector2i);
private:
		towerAUI tempTowerAUI;
		towerBUI tempTowerBUI;
		towerCUI tempTowerCUI;
		towerDUI tempTowerDUI;
};


bool loadTextures();



#endif // UI_HH

