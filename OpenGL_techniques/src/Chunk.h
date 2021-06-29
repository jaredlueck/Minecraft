#include "game_settings.h"
#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	int x;
	int y;
	int z;
};

class Chunk
{
public:
	const static int chunkWidth = 16;
	const static int chunkHeight = 64;
	BlockType blocks[chunkWidth][chunkHeight][chunkWidth];
private:
	unsigned int VAO;
	std::vector<glm::vec3> vertices;
	void BuildMesh();
};