#include <vector>
#include <thread>
#include <iostream>
#include <stdio.h>
#include "global.h"
#include "init.h"
#include "GL.h"
#include "audio.h"
#include "game.h"
#include <sqlite3.h>
#include <libnotify/notify.h>

#include <X11/Xlib.h>

int main(int argc, char** argv)
{
	notify_init("Player");
	_GAME GAME;
	initGame(std::ref(GAME),argc,argv);
	audio(std::ref(GAME));
	if(GAME.Vid=="yes"){
	XInitThreads();
	std::thread GLThread(GL,std::ref(GAME));
	GLThread.detach();
	}

	GAME_THREAD(std::ref(GAME));
	if(GAME.backend=="sqlite"){
		sqlite3_close(GAME.database);
	}
	else if(GAME.backend=="mysql"){
		mysql_close(GAME.database_2);
	}
	if(GAME.Active)
		return 1;
	return 0;


}
