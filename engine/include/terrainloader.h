#ifndef TERRAINLOADER
#define TERRAINLOADER
#include <vector>
#include <functional>
#include "global.h"
#include "terrain.h"
class TerrainLoader{
public:
	TerrainLoader(_GAME &GAME);
	_GAME GAME;
	vector<std::unique_ptr<Terrain>> Terrains;
	void addTerrain(int x,int y);
	void delTerrain(int index);
	bool checkTerrain(int x,int y);







};

#endif
