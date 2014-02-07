#include "ui.hh"


sf::Texture back_game;// game back ground
sf::Texture pathUI;// corner in the path 
sf::Texture textureTowerA;// Tower A texture
sf::Texture textureTowerB;// Tower B texture
sf::Texture textureTowerC;// Tower C texture
sf::Texture textureTowerD;// Tower D texture
sf::Texture Textureforest;// forest texture
sf::Texture cloud1;
sf::Texture monster1;
sf::Texture monster2;
sf::Texture flymonster1;
sf::Texture flymonster2;
sf::Texture bossmonster;
sf::Texture bulletA;
sf::Texture bulletI;
sf::Texture moon;
sf::Font font;

sf::Texture rangeUI;
sf::Texture rangePurUI;
sf::Texture rangeRed;
sf::Texture rangeGrean;
sf::Texture rightSide;
terrain isDrag=invalidTile;

bool loadTextures(){
 
 
 
    //dragingB=false;
    //dragingC=false;
    //if(!textureTowerA.loadFromFile("src/images/towerA.png")) return false;
    if(!back_game.loadFromFile("src/images/background_game.png")) return false;
    if(!pathUI.loadFromFile("src/images/path.png")) return false;

    if(!Textureforest.loadFromFile("src/images/forest.png")) return false;
    if(!textureTowerA.loadFromFile("src/images/towerA.png")) return false;
    if(!textureTowerB.loadFromFile("src/images/towerB.png")) return false;
    if(!textureTowerC.loadFromFile("src/images/towerC.png")) return false;
    if(!textureTowerD.loadFromFile("src/images/towerD.png")) return false;

    if(!bulletA.loadFromFile("src/images/bulletF.png")) return false;
    if(!bulletI.loadFromFile("src/images/bulletI.png")) return false;


    if(!cloud1.loadFromFile("src/images/cld1.png")) return false;
    if(!moon.loadFromFile("src/images/moon.png")) return false;

    if(!monster1.loadFromFile("src/images/monster1.png")) return false;
    if(!monster2.loadFromFile("src/images/monster2.png")) return false;
    if(!flymonster1.loadFromFile("src/images/flymonster1.png")) return false;
    if(!flymonster2.loadFromFile("src/images/flymonster2.png")) return false;
    if(!bossmonster.loadFromFile("src/images/bossmonster.png")) return false;
    if(!rangeUI.loadFromFile("src/images/range.png")) return false;
    if(!rangePurUI.loadFromFile("src/images/rangePur.png")) return false;
    if(!rangeRed.loadFromFile("src/images/rangeRED.png")) return false;
    if(!rangeGrean.loadFromFile("src/images/rangeGreen.png")) return false;
    if(!rightSide.loadFromFile("src/images/rightSide.png")) return false;

    if(!font.loadFromFile("src/images/Dimbo.ttf")) return false;
    return true;        
}


void UItext(size_t fontsize, const std::string mytext,int X,int Y,sf::Text::Style textStyle,sf::Color myColor){
                sf::Text text(mytext, font);
                text.setCharacterSize(fontsize);
                text.setStyle(textStyle);
                text.setColor(myColor);
                text.setPosition(X,Y);
                window.draw(text);
 
}
void TileUI::tileDraw(std::pair<int, int>pos, terrain te,path_type pType=none){
            switch (te){
 
                case path:
                symbol.setTexture(pathUI);
                break;
 
				case start:
                	symbol.setTexture(pathUI);
					symbol.setTextureRect(sf::IntRect(595,0,85,85));
					break;
				case end:
					symbol.setTexture(pathUI);
				
					symbol.setTextureRect(sf::IntRect(510,0,85,85));
                	break;
                case forest:
                	symbol.setTexture(Textureforest);
					break;



		
                default:
                break;
 
            }
                te=te;
                pType=pType;
                symbol.setPosition(pos.first*85,pos.second*85+40);
				
                if(te==path){
                     
                symbol.setTextureRect(sf::IntRect(0,0,85,85));
             
                if(pType==leftToTop){
                    symbol.setTextureRect(sf::IntRect(85,0,85,85));
                }   
                if(pType==rightToDown){
                    symbol.setTextureRect(sf::IntRect(170,0,85,85));
                }
                if(pType==leftToDown){
                    symbol.setTextureRect(sf::IntRect(255,0,85,85));
                }   
                if(pType==horizontal){
                    symbol.setTextureRect(sf::IntRect(340,0,85,85));
                }
                if(pType==vertical){
                    symbol.setTextureRect(sf::IntRect(425,0,85,85));
                } 
				 if(pType==leftUpDown){
                    symbol.setTextureRect(sf::IntRect(850,0,85,85));
                }  
				 if(pType==rightUpDown){
                    symbol.setTextureRect(sf::IntRect(935,0,85,85));
                }  
				 if(pType==leftRightUp){
                    symbol.setTextureRect(sf::IntRect(680,0,85,85));
                } 
				 if(pType==leftRightDown){
                    symbol.setTextureRect(sf::IntRect(765,0,85,85));
                } 
            }           
            window.draw(symbol);
 
        }



void towerUI::drawAtPositionLevel(std::pair<int, int> pos,float level,bool miniMune,const std::string &nTower,const std::string &sPrice, const std::string &uCost, float range){

			std::ostringstream levelString;
            float rangeRate=(range/300);

		if(miniMune){			
			
			rightSideSymbol.setPosition(863,210);
			
      		levelString<<(level+1);

			rangeTowerSymbol.setScale(rangeRate,rangeRate);

	    	rangeTowerSymbol.setPosition(pos.first*85-int((600*(rangeRate))/2)+42,pos.second*85-int((600*(rangeRate))/2)+85);
			window.draw(rangeTowerSymbol);

     }

    			symbol.setPosition(pos.first*85,pos.second*85+40);
                symbol.setTextureRect(sf::IntRect(level*85,0,85,85));
				animationParameter=(animationParameter+0.1);
					if(onFire && bulletPara>2)  symbol.setTextureRect(sf::IntRect(level*85,(int((10-bulletPara)/3)+1)*85,85,85));//tower animation when shoot 
                window.draw(symbol);

				if(onFire && bulletPara>0){ 
					
					src.x=src.x+(current.x);
					src.y=src.y+(current.y);
               		bulletSymbol.setPosition(int(src.x),int(src.y));
					bulletPara--;
					window.draw(bulletSymbol);
				} else onFire=false;

			if(miniMune){
					window.draw(rightSideSymbol);
					UItext(40,nTower,pos.first*85-(100*rangeRate),pos.second*85-(5*rangeRate),sf::Text::Bold,sf::Color(255,255,255));
				   	UItext(33,"Level:"+levelString .str()+"/3",910,265,sf::Text::Bold,sf::Color(255,255,255));
					
					UItext(20,"Shooting Mode",910,300,sf::Text::Bold,sf::Color(255,255,255));
					UItext(20,"First",910,320,sf::Text::Bold,sf::Color(255,255,255));
					UItext(20,"Fastest",910,340,sf::Text::Bold,sf::Color(255,255,255));
					UItext(20,"Most Helath",910,360,sf::Text::Bold,sf::Color(255,255,255));

					if(level<2) {
						UItext(25,"Upgrade",945,480,sf::Text::Bold,sf::Color(255,255,255));
						UItext(25,"-$"+uCost,950,510,sf::Text::Bold,sf::Color(255,255,255));


					}else {
					UItext(25,"Not",945,480,sf::Text::Bold,sf::Color(255,255,255));
					UItext(25,"Available",930,510,sf::Text::Bold,sf::Color(255,255,255));
					}


						UItext(25,"Sell",965,590,sf::Text::Bold,sf::Color(255,255,255));
						UItext(25,"+$"+sPrice,950,615,sf::Text::Bold,sf::Color(255,255,255));
					

					UItext(25,"Cancel",955,700,sf::Text::Bold,sf::Color(255,255,255));

			}
}
 
 
void towerUI::drawDragAtPosition(sf::Vector2i dragPos){
				float rangeRate=(T_RANGE/300.0);
				rangeTowerSymbol.setScale(float(rangeRate),float(rangeRate));
	    		rangeTowerSymbol.setPosition(dragPos.x-T_RANGE,dragPos.y-T_RANGE);
				window.draw(rangeTowerSymbol);
                symbol.setTextureRect(sf::IntRect(0,0,85,85));
                symbol.setPosition(dragPos.x-40,dragPos.y-40);
                window.draw(symbol);
}


void towerUI::animationBullet(sf::Vector2f s,sf::Vector2f d){
				
				src=s;
				des=d;
				current.x=(des.x-src.x)/10;
				current.y=(des.y-src.y)/10;
				onFire=true;
				bulletPara=10;
				
}


void monsterUI::drawAtPositionDirection(sf::Vector2i newVec,float speed,int direct, int life){
				animationParameter+=speed*0.7;
                if (direct==1)symbol.setTextureRect(sf::IntRect(((int(animationParameter)%4)*85),0,85,85));
                else symbol.setTextureRect(sf::IntRect(((int(animationParameter)%4)*85)+(85),0,-85,85));
				symbol.setPosition (newVec.x,newVec.y);
				//symbol.setTextureRect(sf::IntRect(0, 0, -85, 85));
				if (animationParameter==5) animationParameter=0; 

				
				rectangleLife.setSize(sf::Vector2f(int(life/4), 2));
				rectangleLife.setFillColor(sf::Color::Red);
				rectangleLife.setPosition(newVec.x+20,newVec.y);
				window.draw(symbol);
				window.draw(rectangleLife);
				


}


void GameGroundUI::drawbackground(size_t ground){
                symbol.setPosition(0,0);
                symbol.setTextureRect(sf::IntRect(ground*1024,0,1024,768));
                 
                window.draw(symbol);
                
 
             
        }



void GameGroundUI::UIShowError(float frametime){
	if (frametime-errClock<5.0)
			UItext(20,errMsg,45,735,sf::Text::Bold,sf::Color(255,255,255));
	
}

void GameGroundUI::UISetError(const std::string msg,float frametime){
	errClock=frametime;

	errMsg=msg;



}

void GameGroundUI:: drawCloud(float index){
	
	cloudUI1.setTextureRect(sf::IntRect((index)*320,0,320,110));
	animationParameter=animationParameter+(0.1);
	cloudUI1.setPosition(int(animationParameter+(index*500))%1024,(index)*470);
	window.draw(cloudUI1);


}
void GameGroundUI::drawMoon(){
	
	window.draw(moonUI);

}


terrain DragAndDrop::dragTower(){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                  
                                         
                        //if(isDrag==buyTowerA) tempTowerAUI.drawDragAtPosition(sf::Mouse::getPosition(window));
                            switch (isDrag)
                                {
                                     
                                case buyTowerA:
                                tempTowerBUI.drawDragAtPosition(sf::Mouse::getPosition(window));
                                break;
                                case buyTowerB:
                                tempTowerAUI.drawDragAtPosition(sf::Mouse::getPosition(window));
                                break;
                                case buyTowerC:
                                tempTowerCUI.drawDragAtPosition(sf::Mouse::getPosition(window));
                                break;
  								case buyTowerD:
                                tempTowerDUI.drawDragAtPosition(sf::Mouse::getPosition(window));
                                break;
                                case invalidTile:
                                break;
                                default:
                                break;
                                }
 
                 
            }       
 
         
    return ground;//not complete
}


/*Drag AND Drop*////////
bool DragAndDrop::isRange(sf::Vector2i leftTop,sf::Vector2i rightDown,sf::Vector2i clicked){
             
            if ((leftTop.x<clicked.x) && (rightDown.x>clicked.x) && (leftTop.y<clicked.y) && (rightDown.y>clicked.y)) return true;
            return false;
         
 
}
terrain DragAndDrop::detectTileType(sf::Vector2i Clickedpos){
        if(isRange (buyLiveTL,buyLiveDR,Clickedpos)) return buyLivs;
        if(isRange (buyTowerATL,buyTowerADR,Clickedpos)) return buyTowerA;
        if(isRange (buyTowerBTL,buyTowerBDR,Clickedpos)) return buyTowerB;
        if(isRange (buyTowerCTL,buyTowerCDR,Clickedpos)) return buyTowerC;
        if(isRange (buyTowerDTL,buyTowerDDR,Clickedpos)) return buyTowerD;
        if(isRange (tileRangeTL,tileRangeDR,Clickedpos)) return towerRange;
		
        return invalidTile;
            }
 

 


/*Drag AND Drop*////////


