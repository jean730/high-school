#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "vertex.h"
#include "line.h"
#include "rect.h"
#include "ray.h"
int main(int argc, char **argv){
	sf::Texture texture;
	sf::Texture groundtex;
	texture.loadFromFile("light.png");
	groundtex.loadFromFile("ground.jpg");
	int size=800;
	sf::RenderWindow window(sf::VideoMode(size,size),"fenetre");
	std::vector<Line> lines;
	std::vector<Rect> rects;
	rects.push_back(Rect(-size/2,-size/2,size,size,sf::Color(0,0,0)));
	rects.push_back(Rect(-size/4,-size/4,size/2,size/2,sf::Color(200,200,200)));
	for(float i=1;i<=7;i++){
		for(float j=1;j<=7;j++){
			if(i!=6&&j!=6&&j!=2&&i!=2)
			rects.push_back(Rect(i*100-size/2-20,100*j-20-size/2,40,40,sf::Color(rand()%255,rand()%255,rand()%255)));
		}
	}
	for(float i=0;i<rects.size();i++){
		for(float j=0;j<rects[i].lines.size();j++){
			lines.push_back(rects[i].lines[j]);
		}
	}
	float angle = 0;
	float posX = 0;
	float posY = 0;
	float time = 0;
	sf::RectangleShape rectangle(sf::Vector2f(0,0));
	rectangle.setFillColor(sf::Color(0,0,255));
	sf::View newview = window.getView();
	newview.move(-size/2,-size/2);
	window.setView(newview);
	sf::ConvexShape convex;
	convex.setFillColor(sf::Color(255,255,255));
	convex.setPointCount(3);
	sf::RenderTexture light;
	light.create(size,size);
	sf::View newvie = light.getView();
	newvie.move(-size/2,-size/2);
	light.setView(newvie);
	sf::Sprite ground;
	ground.setTexture(groundtex);
	ground.setPosition(-size/2,-size/2);
	sf::Clock clock;
	sf::Mouse mouse;
	float speed = 1;
	sf::Vector2i mousevec;
	while(true){
	        sf::Event event;
	        while (window.pollEvent(event))
        	{
	        if (event.type == sf::Event::Closed)
                	window.close();
        	}
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//			posX+=speed;
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//			posX-=speed;
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//			posY+=speed;
//		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//			posY-=speed;
//
		mousevec = mouse.getPosition(window);
		if(mousevec.y>=0&&mousevec.y<=size&&mousevec.x>=0&&mousevec.x<=size){
			posX=mousevec.x-size/2;
			posY=mousevec.y-size/2;
		}
		convex.setFillColor(sf::Color(255,
					255,
					255));
		window.draw(ground);
		for(float i=1;i<rects.size();i++){
			rectangle.setSize(sf::Vector2f(rects[i].sx,rects[i].sy));
			rectangle.setPosition(rects[i].x,rects[i].y);
			rectangle.setFillColor(rects[i].color);
			window.draw(rectangle);
		}
		rectangle.setPosition(posX,posY);
		rectangle.setSize(sf::Vector2f(5,5));
		window.draw(rectangle);
		std::vector<Ray> rays;
		std::vector<float> angles;
		std::vector<Vertex> vertices;
		for(float i=0;i<lines.size();i++){
			angles.push_back(atan2 (lines[i].y1-posY,lines[i].x1-posX) * 180 / M_PI-0.0001);
			angles.push_back(atan2 (lines[i].y1-posY,lines[i].x1-posX) * 180 / M_PI);
			angles.push_back(atan2 (lines[i].y1-posY,lines[i].x1-posX) * 180 / M_PI+0.0001);
			angles.push_back(atan2 (lines[i].y2-posY,lines[i].x2-posX) * 180 / M_PI-0.0001);
			angles.push_back(atan2 (lines[i].y2-posY,lines[i].x2-posX) * 180 / M_PI);
			angles.push_back(atan2 (lines[i].y2-posY,lines[i].x2-posX) * 180 / M_PI+0.0001);

		}
		std::sort(angles.begin(),angles.end());
		for(float i=0;i<angles.size();i++){
			rays.push_back(Ray(posX,posY,angles[i]));
		}
		for(float i=0;i<rays.size();i++){
			float minT1=0;
			float minT2=0;
			float T2=0;
			float T1=0;
			for(float j=0;j<lines.size();j++){
				if((lines[j].dx*rays[i].dy - lines[j].dy*rays[i].dx)!=0){
					T2 = (rays[i].dx*(lines[j].y1-rays[i].y) + rays[i].dy*(rays[i].x-lines[j].x1))
						/(lines[j].dx*rays[i].dy - lines[j].dy*rays[i].dx);
				}
				else{
					T2=0;
				}
				T1 = (lines[j].x1+lines[j].dx*T2-rays[i].x)/rays[i].dx;
				if(abs(T1)<abs(minT1) || minT1==0){
					if(T1>0 && T2<1 && T2>0){
						minT1=T1;
						minT2=T2;
					}
				}
			}
			if(minT1>0 && minT2<1 && minT2>0){
				vertices.push_back(Vertex(rays[i].x+rays[i].dx*minT1,rays[i].y+rays[i].dy*minT1));
			}
			else{
			}
		}

		light.clear(sf::Color(150,150,150));
		for(float i=0;i<vertices.size();i++){
			convex.setPoint(0, sf::Vector2f(posX, posY));
			convex.setPoint(1, sf::Vector2f(vertices[i].x, vertices[i].y));
			if(i!=vertices.size()-1){
			convex.setPoint(2, sf::Vector2f(vertices[i+1].x, vertices[i+1].y));
			}
			else{
			convex.setPoint(2, sf::Vector2f(vertices[0].x, vertices[0].y));
			}
			light.draw(convex);
		}
		
		sf::Sprite lightsprite;
		lightsprite.setTexture(texture);
		lightsprite.setPosition(-1000+posX,-1000+posY);
		light.draw(lightsprite,sf::BlendMultiply);
		light.display();
		sf::Sprite sprite(light.getTexture());
		sprite.setPosition(-size/2,-size/2);
		window.draw(sprite,sf::BlendMultiply);
		window.display();
		window.clear();
		speed = clock.getElapsedTime().asMilliseconds()/5.0;
		clock.restart();
	}
}
