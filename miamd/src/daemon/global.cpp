#include "global.h"
#include <fstream>
#include <unistd.h>
void _GAME::mysql_load_callback(MYSQL_ROW argv){
        this->songs[0].push_back(argv[0]);
        this->songs[1].push_back(argv[1]);
        this->songs[3].push_back(argv[2]);
}
int _GAME::sqlite_load_callback(void *GAME, int argc, char **argv, char **column){
	_GAME *gameObject = (_GAME *) GAME;
        gameObject->songs[0].push_back(argv[0]);
        gameObject->songs[1].push_back(argv[1]);
        gameObject->songs[3].push_back(argv[2]);
        return 0;
}
void _GAME::clear_songs(){
	this->songs[0].clear(); // reset the song list
	this->songs[1].clear();
	this->songs[2].clear();
	this->songs[3].clear();
}
void _GAME::reload_songs(){
	std::cout << "Reloading songs..." << std::endl;
	this->clear_songs(); // reset the song list
	load_songs(); // load them
}
void _GAME::set_waypoint(){
	std::string current = mpv_get_property_string(this->mpv,"path");
	std::vector<std::string> save;
	bool do_save = false;
	std::cout << "Saving..." << std::endl;
	std::ofstream waypoint_file;
	waypoint_file.open(std::string(getenv("HOME"))+"/.cache/miamd-waypoint");
	for(int i=0;i<this->songs[1].size();i++){
		if(songs[1][i]==current){
			do_save=true;
		}
		if(do_save){
			save.push_back(songs[1][i]);
			waypoint_file << songs[1][i] << "\n";
		}
	}
	waypoint_file.close();
	std::cout << "Waypoint set." << std::endl;
}
void _GAME::load_waypoint(){
        std::ifstream waypoint_file;
        waypoint_file.open(std::string(getenv("HOME"))+"/.cache/miamd-waypoint");
        std::string song;
	this->clear_songs();
        while(std::getline(waypoint_file,song)){
		songs[0].push_back(song);
		songs[1].push_back(song);
		songs[2].push_back("0");
		songs[3].push_back("0");
	}
	refresh_mpv();
}
void _GAME::load_songs(){
	if(this->backend=="sqlite"){
                if( this->favorite_first == "no" ){
                        sqlite3_exec(this->database,
                                "select * from musics where shit=0 order by favorite,random()",
                                _GAME::sqlite_load_callback,this,NULL);
                }
                else {
                        sqlite3_exec(this->database,
                                "select * from musics where shit=0 order by not favorite,random()",
                                _GAME::sqlite_load_callback,this,NULL);
                }
        }
        else if(this->backend == "mysql"){
                if( this->favorite_first == "no" ){
                        mysql_query(this->database_2,
                                "select * from musics where shit=0 order by favorite,rand()");
                }
                else {
                        mysql_query(this->database_2,
                                "select * from musics where shit=0 order by not favorite,rand()");
                }
                MYSQL_RES *result = mysql_store_result(this->database_2);
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                        this->mysql_load_callback(row);
                }
                mysql_free_result(result);

        }
	refresh_mpv();
}
void _GAME::refresh_mpv(){
	unsigned int countfavorites=0;
	const char* clr[] = {"playlist-clear",NULL};// Clear libmpv playlist
	mpv_command(mpv,clr);
	for(unsigned long int i=0;i<this->songs[1].size();i++){
		const char* com[] = {"loadfile",this->songs[1][i].c_str(),"append-play",NULL};
		mpv_command(mpv,com);
		if( this->songs[3][i] == "1" ){
			countfavorites++;
		}
        }
	printf("Loaded %zu songs. %u of them are marked as favorite.\n",this->songs[1].size(),countfavorites);
	if( this->favorite_first == "no" ){
		printf("Favorites are not played first\n");
	}
	else{
		printf("Favorites are played first\n");
	}
}
