#ifndef LUAFUNC_H
#define LUAFUNC_H
#include "global.h"
#include <lua.hpp>
class luafunc{
public:
	luafunc(_GAME &GAME);
	int createEntity(lua_State *L);
	int setEntityPos(lua_State *L);
	int setEntityAng(lua_State *L);
	int setEntityScale(lua_State *L);
	int setPos(lua_State *L);
	int getPlayerX(lua_State *L);
	int getPlayerY(lua_State *L);
	int getPlayerZ(lua_State *L);
	int sleep(lua_State *L);
	int setSkyColor(lua_State *L);
	int key_up(lua_State *L);
	int key_down(lua_State *L);
	int key_left(lua_State *L);
	int key_right(lua_State *L);
	int key_space(lua_State *L);
	int key_action(lua_State *L);
	int getAngX(lua_State *L);
	int key_shift(lua_State *L);
	int key_ctrl(lua_State *L);
	int setLightPos(lua_State *L);
	int setLightColor(lua_State *L);
	_GAME &GAME;

};
typedef int (luafunc::*mem_func)(lua_State * L);

template <mem_func func>
int dispatch(lua_State * L) {
    luafunc * ptr = *static_cast<luafunc**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}
void luathread(_GAME &GAME,std::string script);
#endif
