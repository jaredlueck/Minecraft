#include "TerrainGeneration.h"
#include "game_settings.h"
extern "C" 
{
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
			}
		}
	}

	chunk.BuildMesh();

	chunksv.push_back(chunk);
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
	for(int i = 0 ; i < (16 * 16) ; i += 16)
		for (int j = 0; j < (16 * 16); j += 16)
		{
			BuildChunk(i, j);
		}
}

BlockType TerrainGeneration::GetBlockType(int x, int y, int z)
{

	BlockType blockType = BLOCK_AIR;

	float s1 = simplex2(x*.01f, z*.01f, 1, 0.25f, 1.0f) * 10;
	float s2 = simplex2(x * 0.01f, z * 0.01f, 1, 0.25f, 1.0f) * 10 * (simplex2(x*0.05, z*0.05f, 1, 0.25f, 1.0));

	float heightMap = s1 + s2;

	float baseLandHeight = Chunk::getHeight() * 0.5f + heightMap;

	float simplexStone1 = simplex2(x * 1.0f, z * 1.0f, 1, 1.0f, 1.0f) * 10;

	float simplexStone2 = simplex2(x * 5.0f, z * 5.0f, 1, 1.0f, 1.0f) * 10 * simplex2(x * 0.3f, z * 0.3f, 1, 1.0f, 1.0f);

	float stoneHeightMap = simplexStone1 + simplexStone2;
	float baseStoneHeight = Chunk::getHeight() * 0.5 + stoneHeightMap;

	if (y <= baseLandHeight)
	{
		blockType = BLOCK_DIRT;

		if (y > baseLandHeight - 1)
			blockType = BLOCK_GRASS;
		if (y <= baseStoneHeight)
			blockType = BLOCK_STONE;
	}

	return blockType;
}

