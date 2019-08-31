#ifndef MISC_H
#define MISC_H
#include <SFML/Graphics.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

sf::Glsl::Mat4 toGlm(glm::mat4 matrix);

sf::Texture loadTexture(std::string name);
sf::Vector3f toGlmv(glm::vec3 matrix);

#endif
