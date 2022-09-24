#version 330 core

in vec2 texCoords;
out vec4 FragColor;
uniform sampler2D;

void main()
{
	vec4 texColor = texture(sampler2D, texCoords);
	FragColor = texColor;
}