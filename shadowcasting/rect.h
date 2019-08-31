#ifndef RECT_H
#define RECT_H
#include <vector>
#include "line.h"
#include <SFML/Graphics.hpp>
class Rect{
public:
	float x=0;
	float sx=0;
	float y=0;
	float sy=0;
	sf::Color color;
	std::vector<Line> lines;
	Rect(float x,float y,float sx,float sy,sf::Color color);
};
#endif
