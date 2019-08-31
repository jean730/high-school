#include <functional>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "global.h"
#include "render.h"
#include "icon.h"
void GL(_GAME &GAME){
	sf::ContextSettings settings;
	settings.attributeFlags = sf::ContextSettings::Core;
	settings.majorVersion = 3;
	settings.minorVersion = 2;
	sf::Window window(sf::VideoMode(GAME.width, GAME.height,32), "Player",
	sf::Style::None,settings);
	window.setIcon(gimp_image.width,gimp_image.height,gimp_image.pixel_data);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(true);
	window.setPosition(sf::Vector2i(
			(sf::VideoMode::getDesktopMode().width-GAME.width)*(GAME.x/100.0f),
			(sf::VideoMode::getDesktopMode().height-GAME.height)*(GAME.y/100.0f)));
	glewInit();
	glClearColor(200.0f / 255, 200.0f / 255, 200.0f / 255, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	GAME.window = &window;
	GAME.WindowDefined = true;
	Render(std::ref(window),std::ref(GAME));

}
