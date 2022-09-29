#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in float textureIndex;

out vec2 texCoords;
out float texInd;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_position = projection * view * model * vec4(pos, 1.0);
	texCoords = textureCoords;
	texInd = textureIndex;

}