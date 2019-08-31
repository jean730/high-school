#include <lua.hpp>
#include <thread>
#include <fstream>
#include <iostream>
#include "global.h"
#include "luafunc.h"
void initGame(_GAME &GAME){
    std::ifstream files("autorun.cfg");
    for (std::string file; std::getline(files, file);){
        std::cout << file << std::endl;
        std::thread(luathread,std::ref(GAME),
                "dofile('lua/"+file+"')"
                ).detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}
