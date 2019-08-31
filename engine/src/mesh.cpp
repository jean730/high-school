#include <vector>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include "mesh.h"
#include "misc.h"
Mesh::Mesh(std::vector<Vertex> vertices,
		std::vector<unsigned int> indices,
		std::vector<Texture> texture){
	this->vertices=vertices;
	this->indices=indices;
	this->textures=texture;
	setup();
}
void Mesh::setup(){
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
  
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
		   &vertices[0],
		   GL_STATIC_DRAW);  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int), 
		&indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)0);

	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(3);	
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}  
void Mesh::draw(sf::Shader &shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

	std::string number;
	std::string name = textures[i].type;
        if(name == "tex")
            number = std::to_string(diffuseNr++);
        else if(name == "spec")
            number = std::to_string(specularNr++);
        else if(name == "norm")
            number = std::to_string(normalNr++);

        shader.setUniform(( name + number).c_str(), (int)i);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, textures[i].id.getNativeHandle());
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
