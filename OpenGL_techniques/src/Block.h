#ifndef BLOCK_H
#define BLOCK_H



#include <glm/glm.hpp>
#include "Shader.h"


class Block
{
	const static float vertices[];

	const static float normal[];

	const static float uv[];

	private:
		glm::vec3 position;
		unsigned int VAO;

	public:
		Block();
		void SetPosition(int x, int y, int z);
		void Draw(Shader& shader);
};

#endif // !BLOCK_H