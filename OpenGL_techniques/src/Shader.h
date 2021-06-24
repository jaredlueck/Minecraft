#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>
#include "LightSource.h"
#include <vector>


class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

        void Bind();
        void Unbind();

        void setInt(const std::string& name, int val);
        void setFloat(const std::string& name, float val);
        void setVec3(const std::string& name, glm::vec3 vec);
        void setMat4(const std::string& name, glm::mat4 mat);

        unsigned int ID;

    private:
        std::string ReadFile(const std::string& path);
        void CompileShader(unsigned int shader);
};

#endif