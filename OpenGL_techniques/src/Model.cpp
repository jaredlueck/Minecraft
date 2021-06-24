#include <glad/glad.h>
#include <filesystem>
#include <tiny_obj_loader.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "Model.h"
#include <unordered_map>
#include <stb_image.h>
#include "Material.h"

Model::Model(const std::string &inputfile)
{
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./materials"; // Path to material files
    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();
    auto &materials = reader.GetMaterials();

    printf("# of vertices  = %d\n", (int)(attrib.vertices.size()) / 3);
    printf("# of normals   = %d\n", (int)(attrib.normals.size()) / 3);
    printf("# of texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
    printf("# of materials = %d\n", (int)materials.size());
    printf("# of shapes    = %d\n", (int)shapes.size());

    std::vector<uint32_t> indices;
    
    std::map<Vertex, uint32_t> uniqueVertices;

    for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

            //hardcode loading to triangles
			int fv = 3;

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                //vertex position
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
                //vertex normal
            	tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];

				// uv
                tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
                tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];

                //copy it into our vertex
				Vertex new_vert;
				new_vert.position.x = vx;
				new_vert.position.y = vy;
				new_vert.position.z = vz;

				new_vert.normal.x = nx;
				new_vert.normal.y = ny;
                new_vert.normal.z = nz;

                new_vert.texCoords.x = tx;
                new_vert.texCoords.y = ty;

                //we are setting the vertex color as the vertex normal. This is just for display purposes
                // new_vert.color = new_vert.normal;

                


				vertices.push_back(new_vert);
			}
			index_offset += fv;
		}
    }

	material.Load(materials[0]);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    // Texture coordinate
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float))); 

    glBindVertexArray(0);   
    
}

void Model::LoadMaterialTextures(tinyobj::material_t mat)
{

    std::filesystem::path dirPath = std::filesystem::current_path();
    std::string diffusePath = dirPath.string() + "/textures/" + mat.diffuse_texname;

    std::string ambientPath = dirPath.string() + "/textures/" + mat.ambient_texname;

    std::string specularPath = dirPath.string() + "/textures/" + mat.specular_texname;

    TextureFromFile(ambientPath.c_str(), "texture_ambient");
    TextureFromFile(diffusePath.c_str(), "texture_diffuse");
    TextureFromFile(specularPath.c_str(), "texture_specular");
    
}

unsigned int Model::TextureFromFile(const char* path, const std::string& type)
{
    int width, height, nrChannels;

    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if(data)
    {

        unsigned int textureID;
        glGenTextures(1, &textureID);

        GLenum format;

        if(nrChannels == 1)
            format = GL_RED;
        else if(nrChannels == 3)
            format = GL_RGB;
        else if(nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Texture texture;
        // texture.id = textureID;
        // texture.path = path;
        // texture.type = type;

        // textures.push_back(texture);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture from path: " << path << std::endl;
        stbi_image_free(data);
    }

    return 0;
}

void Model::Draw(Shader& shader){

	material.SetUniforms(shader);
	
	glBindVertexArray(VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);

}
