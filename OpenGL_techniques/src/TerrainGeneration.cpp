#include "TerrainGeneration.h"
#include "game_settings.h"
#include<algorithm>


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

	noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);

	noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);

	float simplex1 = noise.GetNoise(x*.8f, z*.8f) * 10;
	float simplex2 = noise.GetNoise(x*3.0f, z*3.0f) * 10 * (noise.GetNoise(x*.3f, z*.3f) + .5f);

	float heightMap = simplex1 + simplex2;

	float baseLandHeight = Chunk::chunkHeight * .5f + heightMap;

	noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
	

	float caveNoise1 = noise.GetNoise(x*5.0f, y*10.0f, z*5.0f);
	
	noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);

	float caveMask = noise.GetNoise(x*.3f, z*.3f) + .3f;

	float simplexStone1 = noise.GetNoise(x * 1.0f, z * 1.0f) * 10;
	float simplexStone2 = noise.GetNoise(x * 5.0f, z * 5.0f) * 10 * (noise.GetNoise(x*.3f, z*.3f) + .5f);
	
	float stoneHeightMap = simplexStone1 + simplexStone2;
	float baseStoneHeight = Chunk::chunkHeight * 0.25f + stoneHeightMap;

	if (y <= baseLandHeight)
	{
		blockType = BLOCK_DIRT;

		if (y > baseLandHeight - 1)
			blockType = BLOCK_GRASS;
		if (y <= baseStoneHeight)
			blockType = BLOCK_STONE;
	}

	if (caveNoise1 > std::max(caveMask, .2f))
	{
		blockType = BLOCK_AIR;
	}

	return blockType;
}

