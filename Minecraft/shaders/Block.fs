#version 330 core

in vec2 f_texCoord;
in vec3 f_pos;

uniform sampler2D texture_atlas;

void main()
{
	gl_FragColor = texture(texture_atlas, f_texCoord);
}