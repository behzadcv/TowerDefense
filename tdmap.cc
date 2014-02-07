#include "tdmap.hh"
#include "exception.hh"
#include <string>
#include <fstream>
#include <iostream>
#include "ui.hh"

#define MAP_WIDTH 10

tdMap::tdMap( const std::string fname){
	std::fstream mapfile( fname, std::fstream::in );
	if( !mapfile ){
		throw MapReadError("Opening the file failed");
	}

	while( !mapfile.eof() ){
		std::string iter;
		mapfile >> std::skipws >> iter;
		//dirs last_direction;
		//if it's start point of path
		if( iter == "s" ){
			std::string dir;
			mapfile >> std::skipws >> dir;
			if( dir == "hor" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, start, 0, horizontal ));
				sdir = horizontal;
			}else{
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, start, 0, vertical ));
				sdir = vertical;
			}
			strt = std::make_pair(tiles.back()->getX(), tiles.back()->getY());
		}else if( iter == "t"){ //if it's regular terrain
			int type = 0;
			int height = 0;
			mapfile >> std::skipws >> type >> height;
			tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, type, height, none ));
		}else if( iter == "p" ){ // if it's path
			std::string type2;
			mapfile >> std::skipws >> type2;

			if( type2 == "hor" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, horizontal ));
			}else if(type2 == "ver" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, vertical ));
			}else if(type2 == "lTT" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, leftToTop ));
			}else if(type2 == "rTT" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, rightToTop ));
			}else if(type2 == "lTD" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, leftToDown ));
			}else if(type2 == "rTD" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, rightToDown ));
			}else if(type2 == "lRU" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, leftRightUp ));
			}else if(type2 == "lRD" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, leftRightDown ));
			}else if(type2 == "lUD" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, leftUpDown ));
			}else if(type2 == "rUD" ){
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, rightUpDown ));
			}else{
				tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, path, 0, none ));
			}

		}//if it's endpoint of path
		else if( iter == "e" ) tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, end, 0, none ));
		else if( iter == "f" ) tiles.push_back( new tdTile( tiles.size()%MAP_WIDTH, tiles.size()/MAP_WIDTH, forest, 1000, none ));
	}	//if it's forest

	/*while( !mapfile.eof() ){
		std::string asd;
		mapfile >> std::skipws >> asd;
		std::cout<< asd;
	}*/
}

void tdMap::draw(std::string terminal){
	std::cout<< terminal<< std::endl;
	for( auto i : tiles ){
		std::cout<< i->getPos().first << " "<< i->getPos().second;
	}
}

std::pair<terrain, path_type> tdMap::getTileTypes( sf::Vector2i xy ){
	return std::pair<terrain, path_type>( terrain( tiles.at( xy.y*MAP_WIDTH+xy.x )->getType() ), path_type( tiles.at( xy.y*MAP_WIDTH+xy.x )->getPathType() ));
}

std::pair<terrain, path_type> tdMap::getTileTypes( int x, int y ){
	return std::pair<terrain, path_type>( terrain( tiles.at( y*MAP_WIDTH+x )->getType() ), path_type( tiles.at( y*MAP_WIDTH+x )->getPathType() ));
}

std::pair<terrain, path_type> tdMap::getTileTypes( int ind ){
	return std::pair<terrain, path_type>( terrain( tiles.at( ind )->getType() ), path_type( tiles.at( ind )->getPathType() ));
}

path_type tdMap::getStartDir(){
	return path_type(sdir);//getTileTypes( getStartPos().first, getStartPos().second ).second;
}

void tdMap::draw(){
	for(const auto& i : tiles ){
		i->draw();
	}
}

tdMap::~tdMap(){
	for( auto& i : tiles ){
		delete i;
	}
}

