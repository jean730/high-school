#include <vector>
#include "rect.h"
#include "line.h"
#include <SFML/Graphics.hpp>
Rect::Rect(float x,float y,float sx,float sy,sf::Color color){
	this->sx=sx;
	this->sy=sy;
	this->x=x;
	this->y=y;
	this->color=color;
	this->lines.push_back(Line(x,y,x+sx,y));
	this->lines.push_back(Line(x,y+sy,x+sx,y+sy));
	this->lines.push_back(Line(x,y,x,y+sy));
	this->lines.push_back(Line(sx+x,y,x+sx,y+sy));
}
