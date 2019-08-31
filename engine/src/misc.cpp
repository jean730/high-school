#include <SFML/Graphics.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

sf::Glsl::Mat4 toGlm(glm::mat4 matrix){
    return sf::Glsl::Mat4(glm::value_ptr(matrix));
}

sf::Texture loadTexture(std::string name){
    sf::Texture texture;
    sf::Image image;
    image.loadFromFile(name);
    image.flipVertically();
    image.flipHorizontally();
    texture.loadFromImage(image);
    texture.setSmooth(true);
    texture.setRepeated(true);
    texture.generateMipmap();
    return texture;
}
sf::Vector3f toGlmv(glm::vec3 matrix){
    return sf::Vector3f(matrix.x,matrix.y,matrix.z);
}


