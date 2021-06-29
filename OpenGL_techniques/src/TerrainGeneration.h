#ifndef TERRAIN_H
#define TERRAIN_H

#include "Block.h"
#include <vector>
#include "Shader.h"
#include "game_settings.h"
#include <unordered_map>
#include "Chunk.h"

struct ChunkPos
{
	int x;
	int y;
	ChunkPos(int x, int y) : x(x), y(y) {}
};

class TerrainGeneration
{
	public:
		void BuildChunk();
		void RenderChunk(Shader& shader);
	private:
		std::vector<Block> blocksv;
		std::unordered_map<ChunkPos, Chunk> chunks;
};

#endif // !TERRAIN_H




