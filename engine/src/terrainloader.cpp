#include "terrainloader.h"
#include "global.h"
TerrainLoader::TerrainLoader(_GAME &GAME){
	this->GAME = GAME;
}
void TerrainLoader::addTerrain(int x,int y){
	this->Terrains.push_back(unique_ptr<Terrain>(new Terrain(3,1,x,y,120,400,8,std::ref(this->GAME))));
	this->Terrains[this->Terrains.size()-1]->loadToVAO();
}
bool TerrainLoader::checkTerrain(int x,int y){
	for(int i=0;i<this->Terrains.size();i++){
		if(this->Terrains[i]->gridX == x && this->Terrains[i]->gridZ == y){
			return true;
		}
	}
	return false;
}
void TerrainLoader::delTerrain(int index){
	auto iterator = this->Terrains.begin()+index;
	this->Terrains.erase(iterator);
}
