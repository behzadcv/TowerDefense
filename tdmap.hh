#ifndef TDMAP_HH
#define TDMAP_HH

#include <vector>
#include <string>
#include <utility>
#include "ui.hh"

/*
class tdMap
Class for loading, storing and accessing map data

Format is plain simple block-style:
[<x><y>]<l1><l2><l3>...<ln>
[x and y are  dimensions of the map as tiles] -->no longer used
l1, l2 etc consist data of x tiles (l -> line)
so it would be like
<l1> = <s1><s2><s3>...<sx>
where
s1, s2 etc represents data of one tile

tile format is as follows:
<id><type><height>

example:
sx
px
pe
this map converted into file would look like this:
2 3 s t 1 0 p t 1 0 p p e s t 1 0 p t 1 0 p p e s t 1 0 p t 1 0 p p e s t 1 0 p t 1 0 p p e s t 1 0 p t 1 0 p p e s t 1 0 p t 1 0 p p e

format may change to something more appropriate if needed
*/

//enum to make reading of the format easier/more clear
/*typedef enum{
	path,
	ground,
	forest,
	swamp,
	start,
	end
}terrain;*/ //moved to ui.hh

/*
function
paramers sf::Vector2i
returns
terraintype && path_type as std::pair


*/

//tile utility, quite self-explanatory
/*typedef enum{
	up,
	down,
	left,
	right,
	same
}dirs;
*/
class tdTile{
private:
	int x, y, type, height, pt;
	TileUI ui;
	std::pair<int, int> pos;
public:
	tdTile( int _x, int _y, int _type, int _height, int _pt ) : x(_x), y(_y), type(_type), height(_height), pt(_pt) {
		pos = std::make_pair(x, y);
	}

	int getX(){ return x; }
	int getY(){ return y; }
	std::pair<int, int>& getPos(){ return pos; }//return std::pair<int, int>(x, y); }
	int getType(){ return type; }
	int getPathType(){ return pt; }
	int getHeight(){ return height; }

	void draw(){ ui.tileDraw(std::pair<int,int>(x, y), terrain(type), path_type(pt)); }
};

class tdMap{
private:
	size_t countOfStarts;
	size_t countOfEnds;

	std::pair<int, int> strt;
	path_type sdir;

	std::vector<tdTile*> tiles;


public:
	tdMap();
	tdMap( std::string );
	tdMap( const tdMap& ) = delete;		//rule of three
	tdMap& operator= ( const tdMap& ) = delete;		//also rule of three
	~tdMap();

	std::pair<terrain, path_type> getTileTypes( sf::Vector2i );
	std::pair<terrain, path_type> getTileTypes( int x, int y );
	std::pair<terrain, path_type> getTileTypes( int );

	void draw(std::string);	//this draws into terminal
	void draw();	//this draws into actual graphical game screen

	std::pair<int, int> getStartPos(){
		return strt;
	}
	path_type getStartDir();

};





#endif // TDMAP_HH

