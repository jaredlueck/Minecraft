#ifndef CHUNK_H
#define CHUNK_H



#include "game_settings.h"
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"

class Chunk
{
public:
	int xpos;
	int zpos;
	Chunk(int xpos, int ypos);
	const static int chunkWidth = 16;
	const static int chunkHeight = 64;
	static int getHeight() {
		return chunkHeight;
	}
	static int getWidth() {
		return chunkWidth;
	}
	BlockType blocks[chunkWidth + 2][chunkHeight][chunkWidth + 2];
	void Render(Shader& shader);
	void BuildMesh();

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
	unsigned int UV;
	std::vector<glm::vec3> vertices;

	std::vector<glm::vec2> uvs;
	
};

#endif // !CHUNK_H