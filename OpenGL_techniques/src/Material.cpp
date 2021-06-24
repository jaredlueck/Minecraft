#include <glm/glm.hpp>
#include <tiny_obj_loader.h>
#include <glad/glad.h>
#include <iostream>

#include "Material.h"
#include "Shader.h"

Material::Material() {}

void Material::Load(tinyobj::material_t mat)
{

	ambient = glm::vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
	diffuse = glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
	specular = glm::vec3(mat.specular[0], mat.specular[1], mat.specular[2]);
	
	if (mat.ambient_texname == "")
	{
		std::cout << "Material contains no ambient texture" << std::endl;
		useDiffuseAsAmbient = true;
	}
	else
	{
		texture_ambient.Load(mat.ambient_texname);
	}

	texture_diffuse.Load(mat.diffuse_texname);
	texture_specular.Load(mat.specular_texname);

	if (mat.bump_texname == "") 
	{
		useNormalMap = false;
	}
	else 
	{
		useNormalMap = true;
		normalMap.Load(mat.bump_texname);
	}

	shininess = mat.shininess;
 }

void Material::SetUniforms(Shader& shader)
{
	shader.setVec3("material.ambient", ambient);
	shader.setVec3("material.diffuse", diffuse);
	shader.setVec3("material.specular", specular);

	shader.setFloat("material.shininess", shininess);

	shader.setInt("useNormalMap", useNormalMap);

	if (useDiffuseAsAmbient)
	{
		texture_diffuse.Bind(0);
		shader.setInt("texture_ambient", 0);
	}
	else
	{
		texture_ambient.Bind(0);
		shader.setInt("texture_ambient", 0);
	}

	texture_diffuse.Bind(1);
	shader.setInt("texture_diffuse", 1);

	texture_specular.Bind(2);
	shader.setInt("texture_specular", 2);

	normalMap.Bind(3);
	shader.setInt("normal_map", 3);
}

