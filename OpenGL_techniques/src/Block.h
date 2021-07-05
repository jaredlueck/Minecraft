#ifndef BLOCK_H
#define BLOCK_H



#include <glm/glm.hpp>
#include "Shader.h"
#include "game_settings.h"
#include <unordered_map>

struct Tile
{
	float xpos;
	float ypos;
	std::vector<glm::vec2> getUVs()
	{


		std::vector<glm::vec2> uvs =
		{
			glm::vec2(xpos, ypos),// bottom left
			glm::vec2(xpos, ypos + 0.1),// top left
			glm::vec2(xpos + 0.1, ypos + 0.1),// top right

			glm::vec2(xpos, ypos),// bottom left
			glm::vec2(xpos + 0.1, ypos + 0.1),// top right
			glm::vec2(xpos + 0.1, ypos),// bottom right


		};
		return uvs;
	}
	Tile(float xpos, float ypos) : xpos(xpos), ypos(ypos) {}
};

class Block
{
	const static float vertices[];

	const static float normal[];

	const static float uv[];

	private:
		glm::vec3 position;
		unsigned int VAO;
		
	public:
		Tile top, side, bottom;
		Block(Tile tile);
		Block(Tile front, Tile side, Tile bottom);
		void SetPosition(int x, int y, int z);
		void Draw(Shader& shader);
		

		static const std::unordered_map<int, Block> blocks;

};

#endif // !BLOCK_H