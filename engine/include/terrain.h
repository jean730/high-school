#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "global.h"
#include <SFML/Graphics.hpp>
#include <noise/noise.h>
#include "mesh.h"
using namespace std;
class Terrain {
public:
    Terrain(int Occ,int Seed, int X, int Z, int multiplyer, int antiMagnitude, int polyCount, _GAME &GAME);
    void DestroyVAO();
    void loadToVAO();
    void draw(sf::Shader &shader);
    float getHeight(float x,float z);
    float getPValue(float x,float y,float z);
    void setHeight(int x, int z,float y);
    void setColor(int x, int z, sf::Color color);

public:
    int gridX;
    int gridZ;
    bool Ready = false;
    bool Loaded = false;

private:
    float r;
    float g;
    float b;

    int terrainSize = 300;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    _GAME *GAME;
    noise::module::Perlin perlin;
};
#endif
