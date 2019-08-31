#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
class Model{
public:
	Model(std::string path);
	void draw(sf::Shader &shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void load(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat,
		aiTextureType type, std::string typeName);
};
#endif
