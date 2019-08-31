#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec2 TexCoords;
};
struct Texture {
	sf::Texture id;
	std::string type;
	std::string path;
};
class Mesh{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector <Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(sf::Shader &shader);
private:
	unsigned int VAO,VBO,EBO;
	void setup();
};
#endif
