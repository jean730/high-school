#include <vector>
#include <thread>
#include <iostream>
#include <stdio.h>
#include "global.h"
#include "init.h"
#include "GL.h"
#include "game.h"
#include "luafunc.h"
#include "eventListener.h"
#include "shell.h"
#include <X11/Xlib.h>
#include <unistd.h>
#define SHELL
int main(int argc, char** argv)
{
    if(argc==2){
    std::string gamedir = argv[1];
    gamedir="games/"+gamedir;
    chdir(gamedir.c_str());
    }
    else{
    chdir("games/default");
    }
	XInitThreads();
	_GAME GAME;
       	initGame(std::ref(GAME));
	std::thread GameThread(GAME_THREAD,std::ref(GAME));
	GameThread.detach();
	std::thread RenderThread(GL_THREAD,std::ref(GAME));
	RenderThread.detach();
#ifdef SHELL
	std::thread ShellThread(SHELL_THREAD,std::ref(GAME));
	ShellThread.detach();
#endif
	startEventListener(std::ref(GAME));
	if(GAME.Active)
		return 1;
	return 0;

}
