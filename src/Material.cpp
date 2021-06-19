#include <glm/glm.hpp>
#include <tiny_obj_loader.h>

#include "Material.h"

Material::Material(tinyobj::material_t mat) 
: ambient(mat.ambient[0], mat.ambient[1], mat.ambient[2]),
diffuse(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]),
specular(mat.specular[0], mat.specular[1], mat.specular[2]),
shininess(mat.shininess),
ior(mat.ior),
dissolve(mat.dissolve),
illum(mat.illum),
texture_ambient(mat.ambient_texname),
texture_diffuse(mat.diffuse_texname),
texture_specular(mat.specular_texname)
{
    
    if(mat.ambient_texname == "")
    {
        useDiffuseAsAmbient = true;
    }
    

}