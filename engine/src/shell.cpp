#include "global.h"
#include "shell.h"
#include "luafunc.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <thread>
#include <vector>
void SHELL_THREAD(_GAME &GAME){
	std::string buffer = "";
	std::string tbuffer = "";
	std::vector<std::thread> threads;
	while(GAME.Active){
		tbuffer = readline(">>> ");
		add_history(tbuffer.c_str());
		if(tbuffer == ""){
			threads.push_back(std::thread(luathread,std::ref(GAME),buffer));
			threads[threads.size()-1].detach();
			buffer="";
		}
		else if(tbuffer=="exit"){
			GAME.Active=false;
		}
		else{
			buffer+=tbuffer+"\n";
		}
	}

}
