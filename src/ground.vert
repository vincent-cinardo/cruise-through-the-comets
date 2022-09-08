#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

//out vec2 text;

void main() 
{
	//gl_Position = transform * vec4(pos, 1.0);
	gl_Position = projection * view * model * vec4(pos, 1.0);
	//vec2 text = tex;
}