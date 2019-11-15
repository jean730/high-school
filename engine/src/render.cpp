#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "global.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "misc.h"
#include "entity.h"
#include "terrain.h"
#include "terrainloader.h"

void Render(sf::Window &window, _GAME &GAME){

	sf::Shader shader;
	shader.loadFromFile("assets/shaders/model.vert", "assets/shaders/model.frag");
	sf::Clock clock = sf::Clock();
	glm::mat4 view;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glCullFace(GL_MULTISAMPLE);
	glGenerateMipmap(GL_TEXTURE_2D);
//	glEnable(GL_CLAMP_TO_BORDER);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	int mx;
	int my;
	GAME.Texture=loadTexture("assets/textures/tdiff.png");
	GAME.Norm=loadTexture("assets/textures/tnorm.png");
	GAME.Spec=loadTexture("assets/textures/tspec.png");
	TerrainLoader Terrains = TerrainLoader(std::ref(GAME));

	int ChunkDistance = 2;
	while(GAME.Active){
		int GridPlayerX = GAME.Position_X/300;
		int GridPlayerZ = GAME.Position_Z/300;
		for(int i=0;i<Terrains.Terrains.size();i++){
			if((Terrains.Terrains[i]->gridX-GridPlayerX)*(Terrains.Terrains[i]->gridX-GridPlayerX)>ChunkDistance*ChunkDistance ||
			    (Terrains.Terrains[i]->gridZ-GridPlayerZ)*(Terrains.Terrains[i]->gridZ-GridPlayerZ)>ChunkDistance*ChunkDistance){
				Terrains.delTerrain(i);
			}

		}
		for(int i=GridPlayerX-ChunkDistance;i<=GridPlayerX+ChunkDistance;i++){
			for(int j=GridPlayerZ-ChunkDistance;j<=GridPlayerZ+ChunkDistance;j++){
				if(!Terrains.checkTerrain(i,j)){
					Terrains.addTerrain(i,j);	
				}
			}
		}
		mx = sf::Mouse::getPosition().x - window.getSize().x / 2;
		my = sf::Mouse::getPosition().y - window.getSize().y / 2;
		if(GAME.focus){
			sf::Mouse::setPosition(
				sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
			GAME.angX += (float)mx / 10;
			GAME.angY += (float)my / 10;
		}
		if (GAME.angX > 360) {
			GAME.angX -= 360;
		}
		else if (GAME.angX < 0) {
			GAME.angX += 360;
		}
		if (GAME.angY > 179) {
			GAME.angY = 179;
		}
		else if (GAME.angY < 1) {
			GAME.angY = 1;
		}
		glClearColor((float)GAME.SKY_COLOR.r/255.0f,
				(float)GAME.SKY_COLOR.g/255.0f,
				(float)GAME.SKY_COLOR.b/255.0f,
				1.0f);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 		glClear(GL_DEPTH_BUFFER_BIT);
		sf::Shader::bind(&shader);
		glm::mat4 model(1.0);
		glDepthFunc(GL_LESS);
		view = glm::lookAt(glm::vec3(
			GAME.Position_X, GAME.Position_Y, GAME.Position_Z),
			glm::vec3(
			GAME.Position_X + cos(glm::radians(GAME.angX))*sin(glm::radians(GAME.angY)),
			GAME.Position_Y + cos(glm::radians(GAME.angY)),
			GAME.Position_Z + sin(glm::radians(GAME.angX))*sin(glm::radians(GAME.angY))),
			glm::vec3(0, 1, 0));

		glm::mat4 proj = glm::perspective(
			glm::radians(70.0f),
			(float)window.getSize().x / (float)window.getSize().y
			, 1.0f, 10000.0f);

		shader.setUniform("action",GAME.KEY_Action);
		shader.setUniform("model", toGlm(model));
		shader.setUniform("view", toGlm(view));
		shader.setUniform("projection", toGlm(proj));
		shader.setUniform("time",clock.getElapsedTime().asMilliseconds());
		shader.setUniform("viewPos", sf::Glsl::Vec3(GAME.Position_X,
			GAME.Position_Y,
			GAME.Position_Z));


    		shader.setUniform("eyes", sf::Glsl::Vec3(
			cos(glm::radians(GAME.angX))*sin(glm::radians(GAME.angY)),
			cos(glm::radians(GAME.angY)),
			sin(glm::radians(GAME.angX))*sin(glm::radians(GAME.angY))));
        for(int i=0;i<LIGHTS;i++){
    		shader.setUniform("lights["+std::to_string(i)+"].position", GAME.lights[i].position);
    		shader.setUniform("lights["+std::to_string(i)+"].ambient", GAME.lights[i].ambient);
    		shader.setUniform("lights["+std::to_string(i)+"].diffuse", GAME.lights[i].diffuse);
        }
		glm::mat4 terr = model;
		terr = glm::translate(terr, glm::vec3(0,0,0));
		terr = glm::scale(terr,glm::vec3(10,0.1,10));
    		for(int i=0;i<Terrains.Terrains.size();i++){
        		Terrains.Terrains[i]->draw(std::ref(shader));
		}
		for(int i=0;i<(int)GAME.Entities.size();i++){
			if(GAME.Entities[i].models.size()==0){
				GAME.Entities[i].models.push_back(
						Model(GAME.Entities[i].file));
			}
			glm::mat4 ent = model;
			ent = glm::translate(ent, glm::vec3(GAME.Entities[i].x,
						GAME.Entities[i].y,
                                                GAME.Entities[i].z));
			ent = glm::rotate(ent,GAME.Entities[i].ay,glm::vec3(0.0f,1.0f,0.0f));
			ent = glm::rotate(ent,GAME.Entities[i].ax,glm::vec3(1.0f,0.0f,0.0f));
			ent = glm::rotate(ent,GAME.Entities[i].az,glm::vec3(0.0f,0.0f,1.0f));
			ent = glm::scale(ent,glm::vec3(GAME.Entities[i].sx,
                                                GAME.Entities[i].sy,
                                                GAME.Entities[i].sz));

			shader.setUniform("model", toGlm(ent));
			GAME.Entities[i].draw(std::ref(shader));
		}
		
	
		window.display();
	}
}
