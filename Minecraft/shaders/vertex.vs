#version 330 core

layout (location = 0) in vec3 pos; 
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 f_texCoord;
out vec3 f_normal;
out vec3 f_pos;

flat out vec3 cam_world;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    f_texCoord = texCoord;
	f_normal = mat3(transpose(inverse(model))) * normal;
	f_pos = vec3(model * vec4(pos, 1.0));;
	cam_world = (inverse(view) * vec4(0,0,0,1)).xyz;

};