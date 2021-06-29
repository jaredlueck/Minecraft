#include "Chunk.h"
#include "game_settings.h"

void Chunk::BuildMesh()
{
	for (int x = 1; x < chunkWidth; x++)
		for (int z = 1; z < chunkWidth; z++) 
			for (int y = 0; y < chunkHeight; y++)
			{
				glm::vec3 blockPos = glm::vec3(x-1, y, z-1);
				
				if (blocks[x][y][z] != BLOCK_AIR)
				{
					// if there is no land above, build air.
					if (y < chunkHeight - 1 && blocks[x][y + 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
					}
					// bottom face
					if (y > 0 && blocks[x][y - 1][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 1.0f));
					}
					// front
					if (blocks[x][y][z - 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(0.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(0.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
					}
					// right
					if (blocks[x + 1][y][z] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 0.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
					}
					// back
					if (blocks[x][y][z + 1] == BLOCK_AIR)
					{
						vertices.push_back(blockPos + glm::vec3(1.0f, 0.0f, 1.0f));
						vertices.push_back(blockPos + glm::vec3(1.0f, 1.0f, 1.0f));
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
					}

				}
			}
}
