#ifndef WAVE_HH
#define WAVE_HH

#include "monster.hh"
//#include "player.hh"
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

class Player;

class wave{
protected:
	std::list<Monster*> deadMonsters;
	std::list<Monster*> deployed;
public:
	wave();
	wave( const wave& ) = delete;
	wave& operator=( const wave& ) = delete;

	virtual int countMonsters() = 0;
	virtual std::list<Monster*>& getMonstersList() = 0;
	virtual void deployMonster(float, tdMap&) = 0;
	virtual void killMonster(Monster*) = 0;
	virtual void ascendMonster(Monster*) = 0;
	virtual void paused(float) = 0;
	virtual bool isDeployed() = 0;
	virtual void update( float, tdMap& ) = 0;

	~wave();
};

class testWave : public wave{
protected:
	int wnum;
	//std::list<Monster*> deadMonsters;
	//std::list<Monster*> deployed;
	int wsize;
	int mdepl;
	bool deployedd;
	Player* pl;

public:
	testWave() :  wnum(1), wsize(0), mdepl(0), deployedd(false) {}
	testWave( int _w, Player* _pl ) : wnum(_w), mdepl(0), deployedd(false), pl(_pl) { wsize = int(wnum*1.5); }

	testWave( const wave& ) = delete;
	testWave& operator=( const wave& ) = delete;

	int countMonsters(){ return deployed.size(); }

	std::list<Monster*>& getMonstersList() { return deployed; }

	void deployMonster(float, tdMap& );
	void killMonster(Monster*);
	void ascendMonster(Monster*);
	//void killMonster(Monster*);
//	void killMonster( Monster* );
	void paused(float);

	bool isDeployed(){
		return deployedd;
	}

	void update( float, tdMap& );


	~testWave(){
		while( deployed.size() != 0 ){
			delete deployed.back();
			deployed.remove(deployed.back());
			std::cout<< "Deleted living monster\n";
		}
		while( deadMonsters.size() != 0 ){
			delete deadMonsters.back();
			deadMonsters.remove(deadMonsters.back());
			std::cout<< "Deleted dead monster\n";
		}
	}
};

class infinityWave : public wave{
public:
	infinityWave(Player* _pl)/* : wave()*/{
		pl = _pl;
		start_time = 0.0;
		hp_incr = 0.0;
		sp_incr = 0.0;
		sOD_incr = 0.0;
		mOD_incr = 0.0;
		dpld = 0;
		fly_propab = 0;
		monster_difficulty = 0;
	}
	void deployMonster(float, tdMap&);

	void update( float, tdMap& );
	void paused(float);

	int countMonsters(){return dpld;};
	std::list<Monster*>& getMonstersList(){return deployed;};
	void killMonster(Monster*);
	void ascendMonster(Monster*);
	bool isDeployed(){return false;}


private:
	float start_time;
	float hp_incr;
	float sp_incr;
	float sOD_incr;
	float mOD_incr;
	int fly_propab;
	int monster_difficulty;
	//std::list<Monster*> deadMonsters;
	//std::list<Monster*> deployed;
	Player* pl;

	int dpld;


	//float spawn_rate;

};

class arcadeWave : public wave{
public:
	arcadeWave(int _wnum, Player* _pl){
		pl = _pl;
		start_time = 0.0;
		hp_incr = 0.0;
		sp_incr = 0.0;
		sOD_incr = 0.0;
		mOD_incr = 0.0;
		dpld = 0;
		deployedd = false;
		mdepl = 0;


		monster_difficulty = 0;
		fly_propab = 20;

		wnum = _wnum;
		wsize = int(( 25*wnum / 20 )+cos(0.7*wnum)+3);//2;//int( 30*wnum / 20 );
		std::cout<<wsize<<std::endl;

	}
	void deployMonster(float, tdMap&);

	void update( float, tdMap& );
	void paused(float);

	int countMonsters(){return deployed.size();};
	std::list<Monster*>& getMonstersList(){return deployed;};
	void killMonster(Monster*);
	void ascendMonster(Monster*);
	bool isDeployed(){return deployedd;}


private:
	float start_time;
	float hp_incr;
	float sp_incr;
	float sOD_incr;
	float mOD_incr;

	int wsize;
	int mdepl;
	bool deployedd;
	//std::list<Monster*> deadMonsters;
	//std::list<Monster*> deployed;
	Player* pl;

	int dpld;
	int wnum;

	int monster_difficulty;
	int fly_propab;
	//float spawn_rate;

};

class normalWave : public wave{
public:
	normalWave(int _wnum, Player* _pl){
		pl = _pl;
		start_time = 0.0;
		hp_incr = 0.0;
		sp_incr = 0.0;
		sOD_incr = 0.0;
		mOD_incr = 0.0;
		dpld = 0;
		deployedd = false;
		mdepl = 0;

		wnum = _wnum;
		wsize = int(( 25*wnum / 20 )+cos(0.7*wnum)+5);

		monster_difficulty= 0;
		fly_propab= 20;

	}
	void deployMonster(float, tdMap&);

	void update( float, tdMap& );
	void paused(float);

	int countMonsters(){return deployed.size();};
	std::list<Monster*>& getMonstersList(){return deployed;};
	void killMonster(Monster*);
	void ascendMonster(Monster*);
	bool isDeployed(){return deployedd;}


private:
	float start_time;
	float hp_incr;
	float sp_incr;
	float sOD_incr;
	float mOD_incr;

	int wsize;
	int mdepl;
	bool deployedd;
	//std::list<Monster*> deadMonsters;
	//std::list<Monster*> deployed;
	Player* pl;

	int dpld;
	int wnum;

	int monster_difficulty;
	int fly_propab;


	//float spawn_rate;

};

class baseWaves{

public:
	baseWaves(): current_wave(0), dt1(0.0), dt2(0.0), deploying(false) {}
	baseWaves( const baseWaves& ) = delete;
	baseWaves& operator=( const baseWaves& ) = delete;

	virtual ~baseWaves()/*{
		//for( std::vector<wave*>::iterator it; it != waves.end(); it++){
		//	waves.erase(it);
		//	std::cout<<"Deleted a single wave from baseWaves\n";

		//	delete *it;
		//}
	}*/ = 0;

	/*void deploy(){
		if(deploying) return;

		current_wave++;
		std::cout<<"Deploying new wave (" << current_wave << ")\n";
		waves.push_back( new testWave(current_wave, pl));
		deploying = true;
	}*/

	virtual void deploy(float){
		/*if(deploying) return;
		if(ft)
			current_wave++;
		std::cout<<"Deploying new wave (" << current_wave << ")\n";
		waves.push_back( new testWave(current_wave, pl));
		deploying = true;*/
	}

	wave& getCurrentWave(){
		return *(waves.at(current_wave-1));
	}

	void update( float, tdMap& );

protected:
	std::vector<wave*> waves;	//std::vector for easy indexing, float for time used to beat the wave and wave* should be quite self-explaining
	int current_wave;

	float dt1;
	float dt2;

	bool deploying;

	Player* pl;

};

class defaultWaves : public baseWaves{
/*private:
	std::vector< std::pair<wave*, float>> waves;	//std::vector for easy indexing, float for time used to beat the wave and wave* should be quite self-explaining
	int current_wave;

	float dt1;
	float dt2;
*/
public:
	defaultWaves(Player* _pl): baseWaves(){
		current_wave = 0;
		dt1 = 0.0;
		dt2 = 0.0;
		deploying = false;
		pl = _pl;
		//map=mmap;
	}

	defaultWaves( const defaultWaves& ) = delete;
	defaultWaves& operator=( const defaultWaves& ) = delete;


	~defaultWaves(){
		for( /*std::vector< wave*>::iterator it; it != waves.end(); it++*/unsigned int i = 0; i < waves.size(); i++){

			std::cout<<"Deleted a single wave from defaultWaves\n";
			//waves.erase( waves.begin(), waves.end() );
			waves.at(i)->~wave();
			delete waves.at(i);
		}
		//for( auto& it; it != waves.end(); it++ ){
			//delete it->first;
		//}
	}

};
//******************************************************************************************************************default waves end *************************************************************************'

//******************************************************************************************************************infinity waves start *************************************************************************'

class infinityWaves : public baseWaves{
private:
	float start_time;
	float spawn_rate;
	float multiple_monsters;
	int multiple_help;
	int multiple_help_freq;
	//int fly_propab;
	//int monster_difficulty;
	//std::vector<infinityWave*> waves;

public:
	infinityWaves(Player* _pl): baseWaves(){
		current_wave = 0;
		dt1 = 0.0;
		dt2 = 0.0;
		deploying = false;
		pl = _pl;
		start_time = 0.0;
		spawn_rate = 1.0;
		multiple_monsters = 1.0;
		multiple_help = 1;
		multiple_help_freq = 10;
		//fly_propab = 0;
		//monster_difficulty = 0;
		//map=mmap;
	}

	infinityWaves( const infinityWaves& ) = delete;
	infinityWaves& operator=( const infinityWaves& ) = delete;

	void deploy( float dt ){
		if(deploying) return;

		//std::cout<< "Deployed infinity wave! Good Luck!\n";
		current_wave++;
		start_time = dt;
		std::cout<<"Deploying infinity wave! (" << current_wave << "). Good Luck!\n";
		waves.push_back( new infinityWave(pl));
		deploying = true;
	}

	void update(float dt, tdMap &map);

	wave& getCurrentWave(){
		return *(waves.front());
	}

	std::string getWaveNumber(){
		std::stringstream ss;
		ss << current_wave;
		return ss.str();
	}

	~infinityWaves(){
		for( /*std::vector< wave*>::iterator it; it != waves.end(); it++*/unsigned int i = 0; i < waves.size(); i++){

			std::cout<<"Deleted a single wave from infinityWaves\n";
			//waves.erase( waves.begin(), waves.end() );
			waves.at(i)->~wave();
			delete waves.at(i);
		}
		//for( auto& it; it != waves.end(); it++ ){
			//delete it->first;
		//}
	}

};
//******************************************************************************************************************infinity waves end *************************************************************************'

//******************************************************************************************************************arcade waves start *************************************************************************'

class arcadeWaves : public baseWaves{
private:
	float start_time;
	float spawn_rate;
	float multiple_monsters;
	int multiple_help;
	float dtx;
	float dtx2;
	float wave_delay;
	int spawn_rate_decreased;


	//std::vector<infinityWave*> waves;

public:
	arcadeWaves(Player* _pl): baseWaves(){
		current_wave = 0;
		dt1 = 0.0;
		dt2 = 0.0;
		dtx = 0.0;
		dtx2 = 0.0;
		deploying = false;
		pl = _pl;
		start_time = 0.0;
		spawn_rate = 1.0;
		multiple_monsters = 1.0;
		multiple_help = 1;
		wave_delay = 0.0;
		spawn_rate_decreased = 0;

		//map=mmap;
	}

	arcadeWaves( const arcadeWaves& ) = delete;
	arcadeWaves& operator=( const arcadeWaves& ) = delete;

	void deploy( float);/*{
		//std::cout << "we are in beginning of deploy" << std::endl;
		if(deploying) return;
		//std::cout << "we passed first if" << std::endl;
		//getCurrentWave().countMonsters();
		if(waves.size() > 0)	{
			//std::cout << "we passed second if" << std::endl;
			if( waves[current_wave-1]->countMonsters() != 0 )	{
				//std::cout << "we are inside third if" << std::endl;
				return;
			}
		}

		if((dt - wave_delay) < 6.0 && current_wave > 0) return;
		current_wave++;
		spawn_rate_decreased = 0;
		start_time = dt;
		std::cout<<"Deploying arcade wave! (" << current_wave << "). Good Luck!\n";
		waves.push_back( new arcadeWave(current_wave, pl));
		deploying = true;
	}
*/
	void update(float dt, tdMap &map);

	wave& getCurrentWave(){
		return *(waves.back());
	}

	std::string getWaveNumber(){
		std::stringstream ss;
		ss << current_wave;
		return ss.str();
	}

	~arcadeWaves(){
		for( unsigned int i = 0; i < waves.size(); i++ ){
			std::cout<<"Deleted a single wave from arcadeWaves\n";
			waves.at(i)->~wave();
			delete waves.at(i);
		}

	}

};

//******************************************************************************************************************arcade waves end *************************************************************************'

class normalWaves : public baseWaves{
private:
	float start_time;
	float spawn_rate;
	float multiple_monsters;
	int multiple_help;
	float dtx;
	float dtx2;
	int spawn_rate_decreased;
	float wave_delay;

public:
	normalWaves(Player* _pl): baseWaves(){
		current_wave = 0;
		dt1 = 0.0;
		dt2 = 0.0;
		dtx = 0.0;
		dtx2 = 0.0;
		deploying = false;
		pl = _pl;
		start_time = 0.0;
		spawn_rate = 1.0;
		multiple_monsters = 1.0;
		multiple_help = 1;
		spawn_rate_decreased = 0;
		wave_delay = 0.0;

	}

	normalWaves( const normalWaves& ) = delete;
	normalWaves& operator=( const normalWaves& ) = delete;

	void deploy( float );/*{
		if(deploying) return;

		if(waves.size() > 0)
			if( waves[current_wave-1]->countMonsters() != 0 )
				return;

		if((dt - wave_delay) < 6.0 && current_wave > 0) return;

		spawn_rate_decreased = 0;
		current_wave++;
		start_time = dt;
		std::cout<<"Deploying normal wave! (" << current_wave << "). Good Luck!\n";
		waves.push_back( new normalWave(current_wave, pl));
		deploying = true;
	}*/

	void update(float dt, tdMap &map);

	wave& getCurrentWave(){
		return *(waves.back());
	}

	std::string getWaveNumber(){
		std::stringstream ss;
		ss << current_wave;
		return ss.str();
	}

	~normalWaves(){
		for( unsigned int i = 0; i < waves.size(); i++ ){
			std::cout<<"Deleted a single wave from normalWaves\n";
			waves.at(i)->~wave();
			delete waves.at(i);
		}

	}

};


#endif

