#include <tiny_obj_loader.h> 
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Shader.h"
#include "Texture.h"

struct Vertex 
{
    glm::vec3 position;
    glm::vec2 texCoords;
};

class Model {

    public:
        Model(const std::string& filepath);
        void LoadMaterialTextures(tinyobj::material_t mat);
        unsigned int TextureFromFile(const char* path, const std::string& type);
        void Draw(Shader& shader);
    private:
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        unsigned int VAO;
        unsigned int VBO;
        unsigned int IBO;

};