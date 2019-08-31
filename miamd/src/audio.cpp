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
std::vector<std::string> songs[3];
void mysql_callback(MYSQL_ROW argv){
	songs[0].push_back(argv[0]);
	songs[1].push_back(argv[1]);
	songs[3].push_back(argv[2]);
}
static int callback(void *unused, int argc, char **argv, char **column){
	songs[0].push_back(argv[0]);
	songs[1].push_back(argv[1]);
	songs[3].push_back(argv[2]);
	return 0;
}

void audio(_GAME &GAME){
	if(GAME.backend=="sqlite"){
		char *buf;
		sqlite3_open(GAME.db_file.c_str(),&GAME.database);
		if( GAME.favorite_first == "no" ){
			sqlite3_exec(GAME.database,
				"select * from musics where shit=0 order by favorite,random()",
				callback,NULL,&buf);
		}
		else {
			sqlite3_exec(GAME.database,
				"select * from musics where shit=0 order by not favorite,random()",
				callback,NULL,&buf);
		}
//		printf("error::%s\n",buf);
	}
	else if(GAME.backend == "mysql"){
		if( GAME.favorite_first == "no" ){
			mysql_query(GAME.database_2,
				"select * from musics where shit=0 order by favorite,rand()");
		}
		else {
			mysql_query(GAME.database_2,
				"select * from musics where shit=0 order by not favorite,rand()");
		}
		MYSQL_RES *result = mysql_store_result(GAME.database_2);
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{
			mysql_callback(row);
		}
		mysql_free_result(result);
		
	}
	mpv_handle *mpv = mpv_create();
	GAME.mpv = mpv;
	mpv_initialize(mpv);
	mpv_set_property_string(mpv,"vid",GAME.Vid.c_str());
	mpv_set_property_string(mpv,"ytdl-format",(std::string("bestvideo[height<=?")+std::to_string(GAME.resolution)+std::string("]+bestaudio/best")).c_str());
	long unsigned int count=0;
	long unsigned int countfavorites=0;
	for(long unsigned int i=0;i<songs[1].size();i++){
			if(i==0){
					const char* com[] = {"loadfile",songs[1][i].c_str(),NULL};
					mpv_command(mpv,com);
			}
			else{
					const char* com[] = {"loadfile",songs[1][i].c_str(),"append",NULL};
					mpv_command(mpv,com);
			}
			count++;
			if( songs[3][i] == "1" ){
				countfavorites++;
			}
	}
	printf("Loaded %ld songs. %ld of them are marked as favorite.\n",count,countfavorites);
	GAME.audio_ready=true;
}
