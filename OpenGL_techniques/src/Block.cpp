#include "Block.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Block::vertices[] = 
{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
};

const float Block::normal[] = 
{
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

const float Block::uv[] =
{
	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 0.0f,  0.0f,
	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,

	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,

	 1.0f,  0.0f,
	 1.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  1.0f,
	 0.0f,  0.0f,
	 1.0f,  0.0f,

	 0.0f,  1.0f,
	 1.0f,  1.0f,
	 1.0f,  0.0f,
	 1.0f,  0.0f,
	 0.0f,  0.0f,
	 0.0f,  1.0f,

	 0.0f,  1.0f,
	 1.0f,  1.0f,
	 1.0f,  0.0f,
	 1.0f,  0.0f,
	 0.0f,  0.0f,
	 0.0f,  1.0f
};

Block::Block(){}

void Block::SetPosition(int x, int y, int z)
{
	position = glm::vec3(x, y, z);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int vb;
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

void Block::Draw(Shader& shader)
{
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);

	shader.setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}