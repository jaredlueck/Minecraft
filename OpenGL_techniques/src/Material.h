#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <tiny_obj_loader.h>

#include "Texture.h"
#include "Shader.h"

class Material
{
    public:
		Material();
        void Load(tinyobj::material_t mat);
		void SetUniforms(Shader& shader);
    private:
        unsigned int uniformBuffer;
        // constants
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 transmittance;
        glm::vec3 emission;

        Texture texture_ambient;
        Texture texture_diffuse;
        Texture texture_specular;

        Texture normalMap;

        float shininess;
        float ior; // index of refraction
        float dissolve;

        int illum; // illumintation model

        bool useDiffuseAsAmbient;

        bool useTransmittance;
        bool useEmission;
        bool useNormalMap;

};

#endif