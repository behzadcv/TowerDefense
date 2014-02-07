#include "wave.hh"
//#include "monster.hh"
#include "monsters.hh"
#include <utility>
#include <iostream>
#include <list>
#include "player.hh"
#include <stdlib.h>

wave::~wave(){
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
wave::wave(){}

void testWave::deployMonster(float dt, tdMap& tdm){
	if(mdepl <= wsize){
		std::cout<<"Deployed a monster; beware!\n";
		deployed.push_back( new easyWalking1( tdm.getStartPos(), tdm.getStartDir(), dt ) );
		mdepl++;
	}
}

void testWave::update( float dt, tdMap& map ){
	if( mdepl-1 == wsize ) deployedd = true;
	for( auto &depMonster : deployed ){
		if(map.getTileTypes(depMonster->getTilePosition().first, depMonster->getTilePosition().second).first == terrain::end){
			ascendMonster(depMonster);
			continue;
		}
		depMonster->update( dt, map );
	}
}

void testWave::killMonster(Monster* mon){
	std::cout<<"Killed monster\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			pl->giveMoney(mon->getMoney());
			pl->giveScore(mon->getScore());
			deadMonsters.push_back( *iter );
			deployed.erase( iter );
			break;
		}
	}
}

void testWave::ascendMonster(Monster* mon){
	std::cout<<"Ascended monster\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			pl->removeLive();
			deadMonsters.push_back( *iter );
			deployed.erase( iter );
			break;
		}
	}
}
//*******************************************************************************************************infinityWave starts *************************************************************
void infinityWave::killMonster(Monster* mon){
	std::cout<<"Killed monster from infinity wave\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			pl->giveMoney(mon->getMoney());
			pl->giveScore(mon->getScore());
			deadMonsters.push_back( *iter );
			deployed.erase( iter );
			break;
		}
	}
}

void infinityWave::ascendMonster(Monster* mon){
	std::cout<<"Ascended monster! Be careful!\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			//std::cout<<"anything?\n";
			pl->removeLive();
			//std::cout<<"anything?2\n";
			deadMonsters.push_back( *iter );
			//std::cout<<"anything?3\n";
			deployed.erase( iter );
			//std::cout<<"anything?4\n";
			break;
		}
	}
}

void infinityWave::deployMonster(float dt, tdMap& tdm){

	//std::srand( dt + dpld );
	if(start_time == 0.0)
		start_time = dt;

	//static float hp_incr = 0.0;
	//static float sp_incr = 0.0;
	//static float sOD_incr = 0.0;
	//static float mOD_incr = 0.0;
	if( dpld == 20 ){
		hp_incr += 175.0;
		sp_incr += 20.0;
		fly_propab = 10;
	}else if( dpld == 40 ){
		hp_incr += 100;
		sp_incr += 10;
		sOD_incr += 50.0;
		mOD_incr += 50.0;
		fly_propab = 20;
	}
	if( dpld % 50 == 0){
		hp_incr += 100.0;
		sp_incr += 10.0;
		sOD_incr += 10.0;
		mOD_incr += 10.0;
		fly_propab = 35;
	}else if( dpld % 75 == 0 && monster_difficulty == 0){
		monster_difficulty = 1;
	}else if( dpld % 150 == 0 && monster_difficulty == 1){
		hp_incr += 150.0;
		sp_incr += 10.0;
		sOD_incr += 20.0;
		mOD_incr += 15.0;
		monster_difficulty = 2;
		fly_propab = 50;
	}else if( dpld % 175 == 0){
		hp_incr += 200.0;
		sp_incr += 20.0;
		sOD_incr += 50.0;
		mOD_incr += 50.0;
		monster_difficulty = 2;
		//fly_propab = 30;
	}/*else if( dpld % 400 == 0){
		hp_incr += 250.0;
		sp_incr += 10.0;
		sOD_incr += 20.0;
		mOD_incr += 20.0;
		//monster_difficulty = 2;
		//fly_propab = 30;
	}*/

	//std::pair<int, int> asd = std::make_pair( 1,2 );
	//path_type asd2 = path_type(horizontal);
	if(monster_difficulty == 0){

		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF1( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(100.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(50.0 + mOD_incr )) );



	}else if(monster_difficulty == 1){
		hp_incr += 0.5;
		sp_incr += 0.5;
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(40.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(30.0 + mOD_incr )) );

	}else{
		hp_incr += 0.60;
		sp_incr += 0.60;
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(40.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityBossMonsterImmune( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(10.0+hp_incr), float((10.0+hp_incr)), float(20.0+sp_incr), int(100.0+sOD_incr), float(30.0 + mOD_incr )) );

	}
	std::cout<<"hp, sp, sod  -> "<<75.0+hp_incr<<", "<<50.0+sp_incr<<", "<<100.0+sOD_incr<<std::endl;
	std::cout<<"Deployed an infinity monster; beware!\n";
	dpld++;
//	mdepl++;

}

void infinityWave::update( float dt, tdMap& map ){
	//if( mdepl-1 == wsize ) deployedd = true;
	std::pair<int, int> currentTile;
	for( auto &depMonster : deployed ){
		depMonster->update( dt, map );
	}
	for( auto &depMonster : deployed ){
		currentTile.first = (depMonster->getCenterPosition().x)/85;
		currentTile.second = (depMonster->getCenterPosition().y - 40)/85;
		if(map.getTileTypes(currentTile.first, currentTile.second).first == terrain::end){
			std::cout<<"asdasd\n";
			this->ascendMonster(depMonster);
			return;
		}
	}

}

//*******************************************************************************************************infinityWave ends *************************************************************

//*******************************************************************************************************arcadeWave starts *************************************************************

void arcadeWave::killMonster(Monster* mon){
	std::cout<<"Killed monster from arcade wave\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			pl->giveMoney(mon->getMoney());
			pl->giveScore(mon->getScore());
			deadMonsters.push_back( *iter );
			deployed.erase( iter );
			break;
		}
	}
}

void arcadeWave::ascendMonster(Monster* mon){
	std::cout<<"Ascended arcane monster! Be careful!\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			//std::cout<<"anything?\n";
			pl->removeLive();
			//std::cout<<"anything?2\n";
			deadMonsters.push_back( *iter );
			//std::cout<<"anything?3\n";
			deployed.erase( iter );
			//std::cout<<"anything?4\n";
			break;
		}
	}
}

void arcadeWave::deployMonster(float dt, tdMap& tdm){
	if( deployedd || mdepl == wsize) return;

	if(start_time == 0.0)
		start_time = dt;

	//static float hp_incr = 0.0;
	//static float sp_incr = 0.0;
	//static float sOD_incr = 0.0;
	//static float mOD_incr = 0.0;
	/*if( dpld == 10 ){
		hp_incr += 175.0;
		sp_incr += 20.0;
	}else if( dpld == 20 ){
		hp_incr += 100;
		sp_incr += 40;
		sOD_incr += 50.0;
		mOD_incr += 50.0;
	}
	if( dpld % 30 == 0){
		hp_incr += 75.0;
		sp_incr += 10.0;
		sOD_incr += 10.0;
		mOD_incr += 10.0;
	}else if( dpld % 50 == 0){
		hp_incr += 100.0;
		sp_incr += 10.0;
		sOD_incr += 50.0;
		mOD_incr += 50.0;
	}*/
	hp_incr = (wnum * wsize)+20;
	sp_incr = (wnum * wsize)/10;
	sOD_incr = (wnum * wsize)/5;
	mOD_incr = (wnum * wsize)/10;

	if( wnum % 10 == 0 ){
		wsize = 1;
		deployed.push_back( new infinityBossMonsterImmune( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float((150.0+hp_incr)*wnum/5), float((150.0+hp_incr)*wnum/5), float(30.0+sp_incr), int((200.0+sOD_incr)*2), float((150.0 + mOD_incr )*2) ));
		dpld++;
		mdepl++;
		fly_propab += 10;
		if( fly_propab > 50 ) fly_propab = 50;
		return;
	}

	if(wnum == 20) monster_difficulty = 1;

	std::srand(dt+dpld);
	if(monster_difficulty == 0){
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF1( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(50.0+hp_incr), float((50.0+hp_incr)), float(30.0+sp_incr), int(100.0+sOD_incr), float(30.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(30.0+hp_incr), float((30.0+hp_incr)), float(30.0+sp_incr), int(100.0+sOD_incr), float(10.0 + mOD_incr )) );

	}else if(monster_difficulty == 1){
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(70.0+hp_incr), float((70.0+hp_incr)), float(30.0+sp_incr), int(100.0+sOD_incr), float(20.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(50.0+hp_incr), float((50.0+hp_incr)), float(30.0+sp_incr), int(100.0+sOD_incr), float(20.0 + mOD_incr )) );
	}




	//std::cout<<"hp, sp, sod  -> "<<75.0+hp_incr<<", "<<50.0+sp_incr<<", "<<100.0+sOD_incr<<std::endl;
	//std::cout<<"Deployed an arcade monster; beware!\n";
	dpld++;
	mdepl++;

}

void arcadeWave::update( float dt, tdMap& map ){
	if( mdepl == wsize && deployed.size() == 0){
		deployedd = true;
		return;
	}
	std::pair<int, int> currentTile;
	for( auto &depMonster : deployed ){
		depMonster->update( dt, map );
	}
	for( auto &depMonster : deployed ){
		currentTile.first = (depMonster->getCenterPosition().x)/85;
		currentTile.second = (depMonster->getCenterPosition().y - 40)/85;
		if(map.getTileTypes(currentTile.first, currentTile.second).first == terrain::end){
			//std::cout<<"asdasd\n";
			this->ascendMonster(depMonster);
			return;
		}
	}

}

//*******************************************************************************************************arcadeWave ends *************************************************************


void normalWave::killMonster(Monster* mon){
	std::cout<<"Killed monster from normal wave\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			pl->giveMoney(mon->getMoney());
			pl->giveScore(mon->getScore());
			deadMonsters.push_back( *iter );
			deployed.erase( iter );
			break;
		}
	}
}

void normalWave::ascendMonster(Monster* mon){
	std::cout<<"Ascended normal monster! Be careful!\n";
	for(auto iter = deployed.begin(); iter != deployed.end(); iter++)	{
		if((*iter) == mon)	{
			//std::cout<<"anything?\n";
			pl->removeLive();
			//std::cout<<"anything?2\n";
			deadMonsters.push_back( *iter );
			//std::cout<<"anything?3\n";
			deployed.erase( iter );
			//std::cout<<"anything?4\n";
			break;
		}
	}
}

void normalWave::deployMonster(float dt, tdMap& tdm){
	if( deployedd || mdepl == wsize) return;

	if(start_time == 0.0)
		start_time = dt;

	hp_incr = (wnum * wsize)+20;
	sp_incr = (wnum * wsize)/10;
	sOD_incr = (wnum * wsize)/5;
	mOD_incr = (wnum * wsize)/10;

	if( wnum >= 5 ){
		hp_incr += 10;
	}if( wnum >= 10 ){
		hp_incr += 10;
		mOD_incr -=20;
	}if( wnum >= 15 ){
		hp_incr += 10;
	}if( wnum >= 20 ){
		hp_incr += 20;
		mOD_incr += 10;
	}if( wnum >= 25 ){
		hp_incr += 10;
		mOD_incr /= 2;
	}if( wnum >= 30 ){
		mOD_incr += 20;
		hp_incr += 30;
	}if( wnum >= 35 ){
		hp_incr += 10;
	}if( wnum >= 40 ){
		hp_incr += 40;
	}if( wnum >= 45 ){
		hp_incr += 10;
	}if( wnum >= 50 ){
		hp_incr += 50;
	}
	hp_incr *= 2;

	if( wnum % 10 == 0 ){
		wsize = 1;
		deployed.push_back( new infinityBossMonsterImmune( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float((350.0+hp_incr)*wnum/5), float((350.0+hp_incr)*wnum/5), float(10.0+sp_incr), int((200.0+sOD_incr)*2), float((500.0 + mOD_incr )*2) ));
		dpld++;
		mdepl++;
		fly_propab += 20;
		if( fly_propab > 50 ) fly_propab = 50;
		return;
	}

	if(wnum == 25) monster_difficulty = 1;

	std::srand(dt+dpld);
	if(monster_difficulty == 0){
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF1( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(70.0+hp_incr), float((70.0+hp_incr)), float(45.0+sp_incr), int(100.0+sOD_incr), float(40.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(50.0+hp_incr), float((50.0+hp_incr)), float(40.0+sp_incr), int(100.0+sOD_incr), float(30.0 + mOD_incr )) );

	}else if(monster_difficulty == 1){
		if( rand() % 100 < fly_propab )
			deployed.push_back( new infinityMonsterF2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Fly, float(90.0+hp_incr), float((90.0+hp_incr)), float(45.0+sp_incr), int(100.0+sOD_incr), float(30.0 + mOD_incr )) );
		else
			deployed.push_back( new infinityMonster2( tdm.getStartPos(), tdm.getStartDir(), dt, MoveType::Walk, float(70.0+hp_incr), float((700.0+hp_incr)), float(40.0+sp_incr), int(100.0+sOD_incr), float(20.0 + mOD_incr )) );
	}
	std::cout<<"Deployed an normal monster; beware!\n";
	dpld++;
	mdepl++;

}

void normalWave::update( float dt, tdMap& map ){
	if( mdepl == wsize && deployed.size() == 0){ deployedd = true; return; }
	std::pair<int, int> currentTile;
	for( auto &depMonster : deployed ){
		depMonster->update( dt, map );
	}
	for( auto &depMonster : deployed ){
		currentTile.first = (depMonster->getCenterPosition().x)/85;
		currentTile.second = (depMonster->getCenterPosition().y - 40)/85;
		if(map.getTileTypes(currentTile.first, currentTile.second).first == terrain::end){
			//std::cout<<"asdasd\n";
			this->ascendMonster(depMonster);
			return;
		}
	}

}


/*void wave::killMonster( Monster* toBeDead ){

	deadMonsters.push_back( toBeDead );
	std::cout<<"Killed monster\n";
	for( auto& vat : deployed ){
		if( vat == toBeDead ){
				deployed.erase( deployed.begin() );
				std::cout<<deadMonsters.size()<<std::endl;
				return;
		}
	}
	std::cout<<"Trying to kill unexisten monster.\n";


}*/
//**************************************************************************************'all wave pauses here ***********************************************************'
void testWave::paused(float frametime)	{
	for(auto it = deployed.begin(); it != deployed.end(); it++)	{
		(*it)->paused(frametime);
	}
}

void infinityWave::paused(float frametime)	{
	for(auto it = deployed.begin(); it != deployed.end(); it++)	{
		(*it)->paused(frametime);
	}
}

void arcadeWave::paused(float frametime)	{
	for(auto it = deployed.begin(); it != deployed.end(); it++)	{
		(*it)->paused(frametime);
	}
}

void normalWave::paused(float frametime)	{
	for(auto it = deployed.begin(); it != deployed.end(); it++)	{
		(*it)->paused(frametime);
	}
}
//*******************************************************************************************************Wave pauses ends *************************************************************

void baseWaves::update( float dt, tdMap &map ){
	dt2 = dt;
	// float monster_dt = dt;
	//std::cout <<"update called\n";
	if( deploying ){
		if( dt2-dt1 > 4 ){
			std::cout<<"baseWaves deployed\n";
			this->getCurrentWave().deployMonster(dt, map);
			dt1 = dt2;
		}
		//this->getCurrentWave().update( dt, map );
	}
	this->getCurrentWave().update( dt, map );
	if( this->getCurrentWave().isDeployed() )
		deploying = false;


	//dt1 = dt2;
}

//*******************************************************************************************************infinityWaves starts *************************************************************

void infinityWaves::update( float dt, tdMap &tmap ){
	dt2 = dt;
	if(!deploying)
		return;

	//std::cout<<"<<< "<<spawn_rate<<"  "<<dt<<" "<<dt1<<" "<<dt2<<">>>      \n";
	if( int(dt - start_time) % 180 < 0.0000001){
		spawn_rate -= float( (dt-start_time)/100000000 );
	}

	if( spawn_rate < 0.1 ){
		spawn_rate = 0.1;
	}

	if( this->waves.front()->countMonsters() == 15 ){
		spawn_rate = 0.7;
	}else if(this->waves.front()->countMonsters() == 20 ){
		spawn_rate = 0.6;
	}else if(this->waves.front()->countMonsters() == 25 ){
		spawn_rate = 0.5;
	}else if(this->waves.front()->countMonsters() == 35 ){
		spawn_rate = 0.4;
	}else if(this->waves.front()->countMonsters() == 75 ){
		spawn_rate = 0.35;
	}else if(this->waves.front()->countMonsters() == 100 ){
		spawn_rate = 0.25;
	}


	if(multiple_help >= 2 && this->waves.front()->countMonsters()%2 == 0 ){
		multiple_monsters = 1.0;
		multiple_help = 1;
	}/*else if(multiple_help > 1 && this->waves.front()->countMonsters()%2 == 0 ){
		multiple_monsters = 1.0;
		multiple_help = 1;
	}*/

	if( dt2-dt1 > (8.0*spawn_rate * multiple_monsters) ){
		std::cout<<"infinityDeploy\n";
		std::cout<<"<<< "<<spawn_rate<<"  "<<dt<<" "<<dt1<<" "<<dt2<<">>>      \n";

		if( this->waves.front()->countMonsters() >= 21 ){
			this->waves.front()->deployMonster(dt, tmap);
			multiple_monsters = 0.4;
			multiple_help = 3;
		}else if( this->waves.front()->countMonsters() %multiple_help_freq == 0 ){
			this->waves.front()->deployMonster(dt, tmap);
			multiple_monsters = 0.6;
			multiple_help = 2;
		}else{
			this->waves.front()->deployMonster(dt, tmap);
		}
		if( this->waves.front()->countMonsters() % 20 == 0)
			spawn_rate -= 0.02;
		dt1 = dt2;
	}

	this->waves.front()->update( dt, tmap );

}
//*******************************************************************************************************infinityWaves ends *************************************************************

//*******************************************************************************************************arcadeWaves starts *************************************************************


void arcadeWaves::update( float dt, tdMap &tmap ){
	dt2 = dt;
	if(!deploying){
		return;
	}

	//if( int(dt - start_time) % 180 < 0.0000001){
	//	spawn_rate -= float( (dt-start_time)/100000000 );
	//}

	if( current_wave % 5 == 0 && spawn_rate_decreased != 1 ){
		spawn_rate -= 0.1;
		spawn_rate_decreased = 1;
	}

	if( spawn_rate < 0.1 ){
		spawn_rate = 0.1;
	}

	if( dt2-dt1 > (1.8*spawn_rate) && !waves.back()->isDeployed()){
		//std::cout<<"normalDeploy\n";
		std::cout<<"<<< "<<spawn_rate<<"  "<<dt<<" "<<dt1<<" "<<dt2<<">>>      \n";

		this->waves.back()->deployMonster(dt, tmap);

		dt1 = dt2;
	}
	this->waves.back()->update( dt, tmap );
	if( this->getCurrentWave().isDeployed() )	{
		deploying = false;
		wave_delay = dt;
	}
	///this->waves.back()->update( dt, tmap );

}

void arcadeWaves::deploy( float dt ){
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
		pl->giveMoney(pl->getMoneyF() * 0.1);
		current_wave++;
		spawn_rate_decreased = 0;
		start_time = dt;
		std::cout<<"Deploying arcade wave! (" << current_wave << "). Good Luck!\n";
		waves.push_back( new arcadeWave(current_wave, pl));
		deploying = true;
	}
//*******************************************************************************************************arcadeWaves ends *************************************************************

void normalWaves::update( float dt, tdMap &tmap ){
	dt2 = dt;
	if(!deploying){
		return;
	}

	//if( int(dt - start_time) % 180 < 0.0000001){
	//	spawn_rate -= float( (dt-start_time)/100000000 );
	//}

	if( current_wave % 5 == 0 && spawn_rate_decreased != 1 ){
		spawn_rate -= 0.05;
		spawn_rate_decreased = 1;
	}

	if( spawn_rate < 0.1 ){
		spawn_rate = 0.1;
	}

	if( dt2-dt1 > (2*spawn_rate) && !waves.back()->isDeployed()){
		//std::cout<<"normalDeploy\n";
		std::cout<<"<<< "<<spawn_rate<<"  "<<dt<<" "<<dt1<<" "<<dt2<<">>>      \n";

		this->waves.back()->deployMonster(dt, tmap);

		dt1 = dt2;
	}
	this->waves.back()->update( dt, tmap );
	if( this->getCurrentWave().isDeployed() )	{
		deploying = false;
		wave_delay = dt;
	}
}

void normalWaves::deploy( float dt ){
	if(deploying) return;

	if(waves.size() > 0)
		if( waves[current_wave-1]->countMonsters() != 0 )
			return;

	if((dt - wave_delay) < 6.0 && current_wave > 0) return;

	spawn_rate_decreased = 0;
	pl->giveMoney(pl->getMoneyF() * 0.1);
	current_wave++;
	start_time = dt;
	std::cout<<"Deploying normal wave! (" << current_wave << "). Good Luck!\n";
	waves.push_back( new normalWave(current_wave, pl));
	deploying = true;
}
baseWaves::~baseWaves(){}
