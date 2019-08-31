#include "global.h"
#include "luafunc.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
luafunc::luafunc(_GAME &__GAME):GAME(__GAME){
}
int luafunc::setPos(lua_State *L){
	this->GAME.Position_X = lua_tonumber(L,1);
	this->GAME.Position_Y = lua_tonumber(L,2);
	this->GAME.Position_Z = lua_tonumber(L,3);
	return 0;
}
int luafunc::setEntityPos(lua_State *L){
	int index=lua_tonumber(L,1);

	this->GAME.Entities[GAME.entityFromUid(index)].x = lua_tonumber(L,2);
	this->GAME.Entities[GAME.entityFromUid(index)].y = lua_tonumber(L,3);
	this->GAME.Entities[GAME.entityFromUid(index)].z = lua_tonumber(L,4);
	return 0;
}
int luafunc::setEntityScale(lua_State *L){
	int index=lua_tonumber(L,1);

	this->GAME.Entities[GAME.entityFromUid(index)].sx = lua_tonumber(L,2);
	this->GAME.Entities[GAME.entityFromUid(index)].sy = lua_tonumber(L,3);
	this->GAME.Entities[GAME.entityFromUid(index)].sz = lua_tonumber(L,4);
	return 0;
}
int luafunc::setEntityAng(lua_State *L){
	int index=lua_tonumber(L,1);

	this->GAME.Entities[GAME.entityFromUid(index)].ax = lua_tonumber(L,2);
	this->GAME.Entities[GAME.entityFromUid(index)].ay = lua_tonumber(L,3);
	this->GAME.Entities[GAME.entityFromUid(index)].az = lua_tonumber(L,4);
	return 0;
}
int luafunc::createEntity(lua_State *L){
	int uid = rand()%RAND_MAX;
	while(this->GAME.entityFromUid(uid)!=-1){
		uid = rand()%RAND_MAX;
	}
	std::string str="";
	str+=lua_tostring(L,1);
	this->GAME.Entities.push_back(Entity(str,uid));
	lua_pushnumber(L,uid);
	std::cout << GAME.Entities[GAME.entityFromUid(uid)].uid << "::" << str << "::" << uid << std::endl;
	return 1;
}
int luafunc::getAngX(lua_State *L){
	lua_pushnumber(L,this->GAME.angX);
	return 1;
}
int luafunc::getPlayerX(lua_State *L){
	lua_pushnumber(L,this->GAME.Position_X);
	return 1;
}
int luafunc::getPlayerY(lua_State *L){
	lua_pushnumber(L,this->GAME.Position_Y);
	return 1;
}
int luafunc::getPlayerZ(lua_State *L){
	lua_pushnumber(L,this->GAME.Position_Z);
	return 1;
}
int luafunc::key_up(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Up);
	return 1;
}
int luafunc::key_down(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Down);
	return 1;
}
int luafunc::key_left(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Left);
	return 1;
}
int luafunc::key_right(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Right);
	return 1;
}
int luafunc::key_space(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Space);
	return 1;
}
int luafunc::key_shift(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Shift);
	return 1;
}
int luafunc::key_ctrl(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Ctrl);
	return 1;
}
int luafunc::key_action(lua_State *L){
	lua_pushnumber(L,this->GAME.KEY_Action);
	return 1;
}
int luafunc::sleep(lua_State *L){
	std::this_thread::sleep_for(std::chrono::milliseconds((int)lua_tonumber(L,1)));
	return 0;
}
int luafunc::setSkyColor(lua_State *L){
	GAME.SKY_COLOR = sf::Color(lua_tonumber(L,1),lua_tonumber(L,2),lua_tonumber(L,3));
	return 0;
}
int luafunc::setLightPos(lua_State *L){
	int index=lua_tonumber(L,1);
	this->GAME.lights[index].position.x = lua_tonumber(L,2);
	this->GAME.lights[index].position.y = lua_tonumber(L,3);
	this->GAME.lights[index].position.z = lua_tonumber(L,4);
	return 0;
}
int luafunc::setLightColor(lua_State *L){
	int index=lua_tonumber(L,1);
	this->GAME.lights[index].ambient.x = lua_tonumber(L,2);
	this->GAME.lights[index].ambient.y = lua_tonumber(L,3);
	this->GAME.lights[index].ambient.z = lua_tonumber(L,4);
	this->GAME.lights[index].diffuse.x = lua_tonumber(L,2);
	this->GAME.lights[index].diffuse.y = lua_tonumber(L,3);
	this->GAME.lights[index].diffuse.z = lua_tonumber(L,4);
	return 0;
}
void luathread(_GAME &GAME,std::string script){
	srand (rand()%RAND_MAX);
	luafunc LUA(std::ref(GAME));
	lua_State *L = luaL_newstate();
	*static_cast<luafunc**>(lua_getextraspace(L)) = &LUA;
	luaL_openlibs(L);
	lua_register(L,"setLightPos", &dispatch<&luafunc::setLightPos>);
	lua_register(L,"setLightColor", &dispatch<&luafunc::setLightColor>);
	lua_register(L,"setPos", &dispatch<&luafunc::setPos>);
	lua_register(L,"setEntityPos", &dispatch<&luafunc::setEntityPos>);
	lua_register(L,"setEntityScale", &dispatch<&luafunc::setEntityScale>);
	lua_register(L,"setEntityAng", &dispatch<&luafunc::setEntityAng>);
	lua_register(L,"createEntity", &dispatch<&luafunc::createEntity>);
	lua_register(L,"getAngX", &dispatch<&luafunc::getAngX>);
	lua_register(L,"getPlayerX", &dispatch<&luafunc::getPlayerX>);
	lua_register(L,"getPlayerY", &dispatch<&luafunc::getPlayerY>);
	lua_register(L,"getPlayerZ", &dispatch<&luafunc::getPlayerZ>);
	lua_register(L,"sleep", &dispatch<&luafunc::sleep>);
	lua_register(L,"setSkyColor", &dispatch<&luafunc::setSkyColor>);
	lua_register(L,"key_up", &dispatch<&luafunc::key_up>);
	lua_register(L,"key_down", &dispatch<&luafunc::key_down>);
	lua_register(L,"key_left", &dispatch<&luafunc::key_left>);
	lua_register(L,"key_right", &dispatch<&luafunc::key_right>);
	lua_register(L,"key_space", &dispatch<&luafunc::key_space>);
	lua_register(L,"key_shift", &dispatch<&luafunc::key_shift>);
	lua_register(L,"key_ctrl", &dispatch<&luafunc::key_ctrl>);
	lua_register(L,"key_action", &dispatch<&luafunc::key_action>);
	luaL_dostring(L,script.c_str());
}
