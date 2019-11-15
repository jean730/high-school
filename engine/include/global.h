#ifndef GLOBAL_H
#define GLOBAL_H
#include <SFML/Window.hpp>
#include <lua.hpp>
#include "entity.h"
#include <SFML/Graphics.hpp>
#define LIGHTS 16
struct Light {
    sf::Glsl::Vec3 position;
    sf::Glsl::Vec3 ambient;
    sf::Glsl::Vec3 diffuse;
    sf::Glsl::Vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
class _GAME{
	public:
	std::vector<Entity> Entities;
	bool Active = true;
	lua_State *L;
    sf::Texture Texture;
    sf::Texture Norm;
    sf::Texture Spec;
	float Position_X = 0;
	float Position_Y = 0;
	float Position_Z = 0;
	float angX = 0;
	float angY = 0;
	bool focus = true;
	bool KEY_Up = false;
	bool KEY_Down = false;
	bool KEY_Left = false;
	bool KEY_Right = false;
	bool KEY_Space = false;
	bool KEY_Shift = false;
	bool KEY_Ctrl = false;
	bool KEY_Action = false;
	float Speed = 10;
    Light lights[LIGHTS];
	sf::Window *window;
	bool WindowDefined = false;
	int Max_Framerate = 1;
	sf::Color SKY_COLOR = sf::Color(10,10,10);
	int entityFromUid(int uid);


};
#endif
