#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 f_texCoord;
out vec3 f_pos;

void main()
{
	f_texCoord = texCoord;
	f_pos = pos;
	gl_Position = projection * view * model * vec4(pos, 1.0f);
}