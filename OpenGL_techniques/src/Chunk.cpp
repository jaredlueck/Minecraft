#include "Chunk.h"
#include "game_settings.h"
#include "Shader.h"
#include <glad/glad.h>
#include "Error.h"

Chunk::Chunk(int xpos, int zpos) : xpos(xpos), zpos(zpos)
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	CheckGLError(__LINE__, __FILE__);
}

void Chunk::BuildMesh()
{
	for (int x = 1; x < chunkWidth + 1; x++)
		for (int z = 1; z < chunkWidth + 1; z++) 
			for (int y = 0; y < chunkHeight; y++)
			{
				glm::vec3 blockPos = glm::vec3(x - 1 + xpos, y, z - 1 + zpos);
				
				if (blocks[x][y][z] != BLOCK_AIR)
				{
					// if there is no land above, build air.
					if (y < chunkHeight - 1 && blocks[x][y + 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));

						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
					}
					// bottom face
					if (y > 0 && blocks[x][y - 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));
					}
					// front
					if (blocks[x][y][z - 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
						
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
					}
					// right
					if (blocks[x + 1][y][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));

						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
					}
					// back
					if (blocks[x][y][z + 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));

						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));
					}
					// left
					if (blocks[x-1][y][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
					}
				}
			}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	CheckGLError(__LINE__, __FILE__);
}

void Chunk::Render(Shader& shader)
{
	glBindVertexArray(VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);

	CheckGLError(__LINE__, __FILE__);
}