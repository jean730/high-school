#include <SFML/System.hpp>
#include <thread>
#include "global.h"
void startEventListener(_GAME &GAME){
	while(GAME.Active){
		sf::Clock clock;


		sf::Event event;
		while(!GAME.WindowDefined){}
		while (GAME.window->pollEvent(event)) {
			if(event.type == sf::Event::GainedFocus) GAME.focus = true;
			if(event.type == sf::Event::LostFocus) GAME.focus = false;
			if (event.type == sf::Event::Closed){
				GAME.window->close();
				GAME.Active = false;
			}
		}
		if(GAME.focus){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) 
				GAME.KEY_Action=true;
			else
				GAME.KEY_Action=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				GAME.KEY_Left=true;
			else
				GAME.KEY_Left=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				GAME.KEY_Right=true;
			else
				GAME.KEY_Right=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				GAME.KEY_Down=true;
			else
				GAME.KEY_Down=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				GAME.KEY_Up=true;
			else
				GAME.KEY_Up=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				GAME.KEY_Space=true;
			else
				GAME.KEY_Space=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				GAME.KEY_Shift=true;
			else
				GAME.KEY_Shift=false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				GAME.KEY_Ctrl=true;
			else
				GAME.KEY_Ctrl=false;




		}
                int sleepLength = 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepLength));


	}

}

