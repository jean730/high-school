#include <vector>
#include <string>
#include <functional>
#include "entity.h"
Entity::Entity(std::string file,int uid){
	this->file=file;
	this->uid = uid;
};
void Entity::draw(sf::Shader &shader){
	for(unsigned int i=0;i<this->models.size();i++){
		this->models[i].draw(std::ref(shader));
	}
};
