#include <cstring>
#include <thread>
#include "global.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpv/client.h>
#include <mpv/render_gl.h>
#include <unistd.h>
#include <math.h> 
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <mysql/mysql.h>

void audio(_GAME &GAME){
	mpv_handle *mpv = mpv_create();
	GAME.mpv = mpv;
	mpv_initialize(mpv);
	mpv_set_property_string(mpv,"vid",GAME.Vid.c_str());
	mpv_set_property_string(mpv,"ytdl-format",(std::string("bestvideo[height<=?")+std::to_string(GAME.resolution)+std::string("]+bestaudio/best")).c_str());
	GAME.load_songs();
	GAME.audio_ready=true;
}
