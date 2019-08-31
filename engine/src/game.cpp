#include <SFML/System.hpp>
#include <thread>
#include "global.h"
void GAME_THREAD(_GAME &GAME){
	while(GAME.Active){
		sf::Clock clock;
                int sleepLength = 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepLength));


	}

}

