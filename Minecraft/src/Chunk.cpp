#include "Chunk.h"
#include "game_settings.h"
#include "Shader.h"
#include <glad/glad.h>
#include "Error.h"
#include "Block.h"

Chunk::Chunk(int xpos, int zpos) : xpos(xpos), zpos(zpos)
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &UV);

	CheckGLError(__LINE__, __FILE__);
}

void Chunk::BuildMesh()
{
	std::vector<glm::vec2> faceUVs;

	for (int x = 1; x < chunkWidth + 1; x++)
		for (int z = 1; z < chunkWidth + 1; z++)
			for (int y = 0; y < chunkHeight; y++)
			{
				glm::vec3 blockPos = glm::vec3(x - 1 + xpos, y, z - 1 + zpos);

				if (blocks[x][y][z] != BLOCK_AIR)
				{
					// top face
					if (y < chunkHeight - 1 && blocks[x][y + 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f)); // top left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f)); // top right

						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f)); // top right
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f)); // bottom right
						
						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.top.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());

			

						
					}
					// bottom face
					if (y > 0 && blocks[x][y - 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));	// top left
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));	// top right

						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));	// bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));	// top right
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));	// bottom right

						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.bottom.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());
					}
					// front
					if (blocks[x][y][z + 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));	// top left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));	// top right

						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));	// bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));	// top right
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));	// bottom right

						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.side.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());
					}
					// right
					if (blocks[x + 1][y][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));	// top left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));	// top right

						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));	// bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));	// top right
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));	// bottom right

						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.side.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());
					}
					// back
					if (blocks[x][y][z - 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));	// top left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));	// top right

						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));	// bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));	// top right
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));	// bottom right

						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.side.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());
					}
					// left
					if (blocks[x - 1][y][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f)); // bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));	// top left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));	// top right

						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));	// bottom left
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));	// top right
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));	// bottom right

						Block block = (Block::blocks.find(blocks[x][y][z])->second);

						faceUVs = block.side.getUVs();

						uvs.insert(uvs.end(), faceUVs.begin(), faceUVs.end());
					}
				}
			}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, UV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * uvs.size(), &uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	CheckGLError(__LINE__, __FILE__);
}

void Chunk::Render(Shader& shader)
{
	glBindVertexArray(VAO);

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);

	CheckGLError(__LINE__, __FILE__);
}