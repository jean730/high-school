#include <vector>
#include "terrain.h"
#include <GL/glew.h>
#include <iostream>
#include "misc.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <noise/noise.h>
using namespace std;
    float Terrain::getPValue(float x,float y,float z){
        float value = perlin.GetValue(x,y,z);
	if(value<0){
		value=0;
	}
        return value;
    }
    Terrain::Terrain(int Occ,int Seed, int X, int Z, int multiplyer, int antiMagnitude, int polyCount,_GAME &GAME)
    {
	this->GAME = &GAME;
        perlin.SetSeed(Seed);
        perlin.SetOctaveCount(Occ);
	perlin.SetPersistence(0.5);
        gridX = X;
        gridZ = Z;
        glm::vec2 uv1;
        glm::vec2 uv2;
        glm::vec2 uv3;
        glm::vec3 v1;
        glm::vec3 v2;
        glm::vec3 v3;
        glm::vec3 dPos1;
        glm::vec3 dPos2;
        glm::vec2 U1;
        glm::vec2 U2;
	glm::vec3 tangent1;
	float normX;
        float normY;
        float normZ;
        int pp = polyCount;
        terrainSize /= pp;
        for (int x = gridX * (terrainSize)*pp; x <= (gridX * (terrainSize) + terrainSize)*pp; x+=pp) {
            for (int z = gridZ * (terrainSize)*pp; z <= (gridZ * (terrainSize) + terrainSize)*pp; z+=pp) {
                    v1 = glm::vec3(x, multiplyer * getPValue((float)x / antiMagnitude, (float)z / antiMagnitude, 0.5), z);          
                    v2 = glm::vec3(x, multiplyer * getPValue((float)x / antiMagnitude, ((float)z + pp) / antiMagnitude, 0.5), (z + pp));
                    v3 = glm::vec3((x + pp), multiplyer * getPValue(((float)x + pp) / antiMagnitude, (float)z / antiMagnitude, 0.5), z);
                    dPos1 = v2 - v1;
                    dPos2 = v3 - v1;
		    float zoom = 0.25;
		    uv1 = glm::vec2(v1.x,v1.z)*zoom;
		    uv2 = glm::vec2(v2.x,v2.z)*zoom;
		    uv3 = glm::vec2(v3.x,v3.z)*zoom;
		    U1 = uv2-uv1;
		    U2 = uv3-uv1;
                    normX = dPos1.y * dPos2.z - dPos1.z * dPos2.y;
                    normY = dPos1.z * dPos2.x - dPos1.x * dPos2.z;
                    normZ = dPos1.x * dPos2.y - dPos1.y * dPos2.x;
		    float f = 1.0f/(U1.x*U2.y-U2.x*U1.y);
		    tangent1.x = f * (U2.y * dPos1.x - U1.y * dPos2.x);
		    tangent1.y = f * (U2.y * dPos1.y - U1.y * dPos2.y);
		    tangent1.z = f * (U2.y * dPos1.z - U1.y * dPos2.z);
		    tangent1 = glm::normalize(tangent1);
		Vertex vertex;
		glm::vec3 vector;
		vector.x = v1.x;
		vector.y = v1.y;
		vector.z = v1.z;
		vertex.Position = vector;
		vector.x = normX;
		vector.y = normY;
		vector.z = normZ;
		vertex.Normal = vector;
		vector.x = tangent1.x;
		vector.y = tangent1.y;
		vector.z = tangent1.z;
		vertex.Tangent = vector;
		glm::vec2 vec;
		vec.x = uv1.x;
		vec.y = uv1.y;
		vertex.TexCoords = vec;
		Vertices.push_back(vertex);
	    }
	}

        terrainSize += 1;
        for (int x = 0; x < terrainSize - 1; x++) {
            for (int z = 0; z < terrainSize - 1; z++) {
                Indices.push_back(x + z * terrainSize + terrainSize + 1);
                Indices.push_back(x + z * terrainSize + terrainSize);
                Indices.push_back(x + z * terrainSize);
                Indices.push_back(x + z * terrainSize + terrainSize + 1);
                Indices.push_back(x + z * terrainSize);
                Indices.push_back(x + z * terrainSize + 1);
            }
        }

    }
    void Terrain::DestroyVAO(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1,&EBO);
    }
    void Terrain::loadToVAO()
    {
	for(int i=0;i<sizeof(Indices);i++){
                std::cout << "Normals:" << Indices[i] << ":" << Vertices[Indices[i]].Normal.x << ":" << Vertices[Indices[i]].Normal.y << ":" << Vertices[Indices[i]].Normal.z << std::endl;
                std::cout << "Tangents:" << Indices[i] << ":" << Vertices[Indices[i]].Tangent.x << ":" << Vertices[Indices[i]].Tangent.y << ":" << Vertices[Indices[i]].Tangent.z << std::endl;
	}
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindVertexArray(VAO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex),
                   &Vertices[0],
                   GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                Indices.size() * sizeof(unsigned int),
                &Indices[0], GL_STATIC_DRAW);

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
    void Terrain::draw(sf::Shader &shader)
    {
        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
	shader.setUniform("tex1", 0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        sf::Texture::bind(&GAME->Texture);

        glActiveTexture(GL_TEXTURE1);
	shader.setUniform("norm1", 1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        sf::Texture::bind(&GAME->Norm);

        glActiveTexture(GL_TEXTURE2);
	shader.setUniform("spec1", 2);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        sf::Texture::bind(&GAME->Spec);

        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    float Terrain::getHeight(float x, float z)
    {
        return Vertices[((int)z * terrainSize + (int)x) * 3 + 1].Position.y;
    }
    void Terrain::setHeight(int x, int z,float y)
    {
//        Vertices[(z * terrainSize + x) * 9 + 1] = y;
        loadToVAO();
    }
    void Terrain::setColor(int x, int z, sf::Color color)
    {
//        Vertices[(z * terrainSize + x) * 9 + 6] = (float)color.r / 255;
//        Vertices[(z * terrainSize + x) * 9 + 7] = (float)color.g / 255;
//        Vertices[(z * terrainSize + x) * 9 + 8] = (float)color.b / 255;
//        loadToVAO();
    }

