#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 texCoord;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(pos, 1.0);
	texCoord = tex;
}