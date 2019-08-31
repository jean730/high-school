#include "global.h"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
void initGame(_GAME &GAME,int argc,char **argv){
	GAME.argc=argc;
	GAME.argv=argv;
	std::ifstream config_file;
	char *HOME = getenv("HOME");
	config_file.open(std::string(HOME)+"/.config/miam.conf");
	std::string config;
	while(std::getline(config_file,config)){
		std::istringstream line(config);
		std::string option;
		std::string value;
		std::getline(line,option,'=');
		std::getline(line,value,'=');
		//std::cout << "Option : " << option << " , Value : " << value << std::endl;
		if(option == "backend"){
			GAME.backend=value;
		}
		else if(option == "mysql_host"){
			GAME.host=value;
		}
		else if(option == "mysql_port"){
			GAME.port=std::stoi(value);
		}
		else if(option == "mysql_login"){
			GAME.login=value;
		}
		else if(option == "mysql_password"){
			GAME.password=value;
		}
		else if(option == "mysql_db"){
			GAME.db_name=value;
		}
		else if(option == "sqlite_db"){
			GAME.db_file=value;
		}
		else if(option == "video"){
			GAME.Vid=value;
		}
		else if(option == "width"){
			GAME.width=std::stoi(value);
		}
		else if(option == "height"){
			GAME.height=std::stoi(value);
		}
		else if(option == "pos_x"){
			GAME.x=std::stoi(value);
		}
		else if(option == "pos_y"){
			GAME.y=std::stoi(value);
		}
		else if(option == "resolution"){
			GAME.resolution=std::stoi(value);
		}
		else if(option == "favorite_first"){
			GAME.favorite_first=value;
		}
	}
	if(GAME.backend=="mysql"){
		GAME.database_2=mysql_init(NULL);
		//fprintf(stderr, "%s", mysql_error(GAME.database_2));
		mysql_real_connect(GAME.database_2,
			GAME.host.c_str(),
			GAME.login.c_str(),
			GAME.password.c_str(), 
			GAME.db_name.c_str(),
			GAME.port
			, NULL, 0);
		//fprintf(stderr, "%s\n", mysql_error(GAME.database_2));
		my_bool reconnect = 1;
		mysql_optionsv(GAME.database_2, MYSQL_OPT_RECONNECT, &reconnect);
		unsigned int timeout= 2;
		mysql_optionsv(GAME.database_2, MYSQL_OPT_CONNECT_TIMEOUT, (void *)&timeout);
	}
	if(argc>=2 && strcmp(argv[1],"novid")==0){
		GAME.Vid="no";
	}

}
