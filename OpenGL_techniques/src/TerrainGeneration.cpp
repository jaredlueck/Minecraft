#include "TerrainGeneration.h"
#include "game_settings.h"
extern "C" {
	#include "noise.h"
}
#include "Chunk.h"


void TerrainGeneration::BuildChunk()
{
	Chunk chunk;
	for (int i = 0; i < chunk.chunkWidth; i++)
	{
		for (int j = 0; j < chunk.chunkWidth; j++)
		{
			for (int k = 0; k < chunk.chunkWidth; k++)
			{
				float n = simplex2(i * .1f, k * .1f, 1, 1.0, 1.0) * 10 + j;

				if (n < 128)
				{
					chunk.blocks[i][j][k] = BLOCK_DIRT;
				}
				else
				{
					chunk.blocks[i][j][k] = BLOCK_AIR;
				}
			}
		}
	}
}

void TerrainGeneration::RenderChunk(Shader& shader)
{
	for (int i = 0; i < blocksv.size(); i++)
	{
		blocksv[i].Draw(shader);
	}
}

