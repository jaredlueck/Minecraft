#ifndef TERRAIN_H
#define TERRAIN_H

#include "Block.h"
#include <vector>
#include "Shader.h"
#include "game_settings.h"
#include <map>
#include "Chunk.h"
#include "FastNoiseLite.h"

struct ChunkPos
{
	int x;
	int z;
	ChunkPos(int x, int y) : x(x), z(y) {}
};

class TerrainGeneration
{
	public:
		void BuildChunk(int xpos, int zpos);
		void RenderChunk(Shader& shader);
		void LoadChunks();
		FastNoiseLite noise;
	private:
		BlockType GetBlockType(int x, int y, int z);
		std::vector<Block> blocksv;
		std::map<ChunkPos, Chunk> chunks;
		std::vector<Chunk> chunksv;
};

#endif // !TERRAIN_H




