#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

struct LightSource 
{
    glm::vec3 lightPos;
    float pad1;

    // float constant;
    // float linear;
    // float quadratic;
    // float pad2;
};

#endif