#ifndef SOUNDSYS_HH
#define SOUNDSYS_HH

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <utility>
#include <iostream>

#include "exception.hh"

class soundSys{
protected:
	std::string fpath;

	//static size_t sBuf_cnt; //sf::SoundBuffers in use
	//static size_t mBuf_cnt; //sf::Musics in use

	static std::map<std::string, sf::SoundBuffer> sBuf_map;
	//static std::map<std::string, sf::Music> mBuf_map;


public:

	soundSys() = delete;
	soundSys( const soundSys& ) = delete;
	soundSys& operator=( const soundSys& ) = delete;

	soundSys(std::string _fpath): fpath(_fpath){}
	~soundSys(){
		std::cout<< sBuf_map.size();
		/*if( sBuf_map.size() == 0) return;
		for( auto& bufs : sBuf_map ){
			bufs.second.~SoundBuffer();
			sBuf_map.erase(sBuf_map.find(bufs.first));
		}*/
	}
};

//soundSys::~soundSys(){}

class sound : public soundSys{
private:
	//std::map<std::string, sf::SoundBuffer> sBuf_map;
	sf::Sound snd;

public:
	sound() = delete;
	sound(std::string _fpath) : soundSys(_fpath) {
		if( sBuf_map.find(_fpath) == sBuf_map.end()){
			sBuf_map.insert( std::make_pair( _fpath, sf::SoundBuffer()));
			if( !sBuf_map.find(_fpath)->second.loadFromFile(_fpath) ){
				sBuf_map.erase( sBuf_map.find(_fpath) );
				throw SoundSysError("Loading sound file failed --> "+_fpath);
			}
		}else{
			fpath = sBuf_map.find(_fpath)->first;
		}
		snd.setBuffer(sBuf_map.find(fpath)->second);
	}//constructor ends

	void play(){
		std::cout<<"played " << fpath << std::endl;
		snd.play();
	}

	~sound(){
		snd.stop();
		snd.~Sound();
		sBuf_map.erase( sBuf_map.find(fpath) );
	}

};



#endif // SOUNDSYS_HH
