#ifndef GLOBAL_H
#define GLOBAL_H
#include <SFML/Window.hpp>
#include <mpv/client.h>
#include <sqlite3.h>
#include <mysql/mysql.h>
#include <iostream>
class _GAME{
	public:
	bool Active = true;
	float Position_X = 0;
	float Position_Y = 0;
	float Position_Z = 0;
	bool KEY_Front = false;
	bool KEY_Back = false;
	bool KEY_Left = false;
	bool KEY_Right = false;
	sf::Window *window;
	bool WindowDefined = false;
	std::string Vid="yes";
	std::string backend="sqlite";
	std::string host="localhost";
	std::string password="";
	std::string login="root";
	std::string favorite_first="yes";
	std::string db_name="musics";
	std::string db_file="musics";
	int port = 3306;
	int Max_Framerate = 1;
	mpv_handle *mpv;
	bool audio_ready=false;
	bool video_ready=false;
	int width = 1280;
	int height = 720;
	int resolution = 720;
	float x = 50;
	float y = 50;
	char **argv;
	int argc;
	sqlite3 *database;
	MYSQL *database_2;
	void mysql_load_callback(MYSQL_ROW argv);
	void load_songs();
	void reload_songs();
	void clear_songs();
	void refresh_mpv();
	void set_waypoint();
	void load_waypoint();
	static int sqlite_load_callback(void *unused, int argc, char **argv, char **column);
	std::vector<std::string> songs[4];
};
#endif
