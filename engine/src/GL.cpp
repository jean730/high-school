#include <functional>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "global.h"
#include "render.h"
void GL_THREAD(_GAME &GAME){
	sf::ContextSettings settings;
	settings.attributeFlags = sf::ContextSettings::Core;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;
	sf::Window window(sf::VideoMode().getFullscreenModes()[0], "Game",
	sf::Style::Fullscreen,settings);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
	GAME.window = &window;
	GAME.WindowDefined = true;
	glewInit();
	Render(std::ref(window),std::ref(GAME));
	

}
