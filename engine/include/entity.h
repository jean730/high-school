#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "model.h"
class Entity{
public:
	Entity(std::string file,int uid);
	void draw(sf::Shader &shader);
	std::vector<Model> models;
	float x=0;
	float y=0;
	float z=0;
	float sx=1;
	float sy=1;
	float sz=1;
	float ax=0;
	float ay=0;
	float az=0;
	std::string file;
	int uid;
};
#endif
