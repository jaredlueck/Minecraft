#include "TerrainGeneration.h"
#include "game_settings.h"
extern "C" {
	#include "noise.h"
}
#include "Chunk.h"


void TerrainGeneration::BuildChunk(int xpos, int zpos)
{
	Chunk chunk(xpos, zpos);
	for (int x = 0; x < chunk.chunkWidth + 2; x++)
	{
		for (int z = 0; z < chunk.chunkWidth + 2; z++)
		{
			for (int y = 0; y < chunk.chunkHeight; y++)
			{
				//float n = GetBlockType((xpos + x - 1), y, (zpos + z - 1));
				chunk.blocks[x][y][z] = GetBlockType((xpos + x - 1), y, (zpos + z - 1));
				/*if (n < 30)
				{
					chunk.blocks[x][y][z] = BLOCK_DIRT;
				}
				else
				{
					chunk.blocks[x][y][z] = BLOCK_AIR;
				}*/
			}
		}
	}

	chunk.BuildMesh();

	chunksv.push_back(chunk);

	/*ChunkPos pos(xpos, zpos);
	chunks[pos] = chunk;*/
}

void TerrainGeneration::RenderChunk(Shader& shader)
{
	for (int i = 0; i < chunksv.size(); i++)
	{
		chunksv[i].Render(shader);
	}
}

void TerrainGeneration::LoadChunks()
{
	for(int i = 0 ; i < 128 ; i += 16)
		for (int j = 0; j < 128; j += 16)
		{
			BuildChunk(i, j);
		}
}

BlockType TerrainGeneration::GetBlockType(int x, int y, int z)
{
	float s1 = simplex2(x*.05f, z*.05f, 1, 0.25f, 1.0f) * 10
		;
	float s2 = simplex2(x * 0.05f, z * 0.05f, 1, 0.25f, 1.0f) * 10 * (simplex2(x*0.05, z*0.05f, 1, 0.25f, 1.0));

	float heightMap = s1 + s2;

	float baseLandHeight = Chunk::getHeight() * 0.5f + heightMap;

	if (y < baseLandHeight) return BLOCK_DIRT;

	return BLOCK_AIR;
	
}

