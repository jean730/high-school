#include <vector>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <functional>
#include <GL/glew.h>
#include "model.h"
#include "misc.h"
Model::Model(std::string path){
	load(path);
}
void Model::draw(sf::Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].draw(std::ref(shader));
    }
}  
void Model::load(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
	    std::cout << "Model loading error :" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
	glm::vec3 vector; 
	vector.x = mesh->mVertices[i].x;
	vector.y = mesh->mVertices[i].y;
	vector.z = mesh->mVertices[i].z; 
	vertex.Position = vector;
	if(mesh->HasNormals()){
	vector.x = mesh->mNormals[i].x;
	vector.y = mesh->mNormals[i].y;
	vector.z = mesh->mNormals[i].z;
	vertex.Normal = vector;
	}
	if(mesh->HasTangentsAndBitangents()){
	vector.x = mesh->mTangents[i].x;
	vector.y = mesh->mTangents[i].y;
	vector.z = mesh->mTangents[i].z;
	vertex.Tangent = vector;
	}
	if(mesh->HasTextureCoords(0) && mesh->mTextureCoords[0]) 
	{
	    glm::vec2 vec;
	    vec.x = -mesh->mTextureCoords[0][i].x;
	    vec.y = -mesh->mTextureCoords[0][i].y;
	    vertex.TexCoords = vec;
	}
	else{
	    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
	}
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

	if(mesh->mMaterialIndex >= 0){
	    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  	    std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
  						aiTextureType_DIFFUSE, "tex");
  	    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  	    std::vector<Texture> specularMaps = loadMaterialTextures(material,
  						aiTextureType_SPECULAR, "spec");
  	    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	    std::vector<Texture> normalMaps = loadMaterialTextures(material,
			    			aiTextureType_HEIGHT, "norm");
  	    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	}  

    return Mesh(vertices, indices, textures);
}  
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat,
		aiTextureType type, std::string typeName){
	std::vector<Texture> textures;
	int count = mat->GetTextureCount(type);
      for(unsigned int i = 0; i < count; i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        std::string temp="";
        temp+=str.C_Str();
        texture.id = loadTexture(directory+"/"+temp);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
  bool noSpec = true;
  if(count!=0 && typeName=="spec")
	 noSpec=false; 
  if(noSpec==true && typeName=="spec"){
      Texture texture;
      std::string temp="";
      temp+="assets/textures/nospec.jpg";
      texture.id = loadTexture(temp);
      texture.type = typeName;
      texture.path = "assets/textures/nospec.jpg";
      textures.push_back(texture);
      std::cout << "Loaded Specular stub texture." << std::endl;

    }
  bool noNormal = true;
  if(count!=0 && typeName=="norm")
	 noNormal=false; 
  if(noNormal==true && typeName=="norm"){
      Texture texture;
      std::string temp="";
      temp+="assets/textures/nonormal.jpg";
      texture.id = loadTexture(temp);
      texture.type = typeName;
      texture.path = "assets/textures/nonormal.jpg";
      textures.push_back(texture);
      std::cout << "Loaded Normal stub texture." << std::endl;

    }
    return textures;
}  
