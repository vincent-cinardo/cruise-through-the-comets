#version 330 core

in vec2 aTextureCoord;
out vec4 FragColor;
uniform sampler2D;

void main()
{
	vec4 texColor = texture(sampler2D, aTextureCoord);
	FragColor = texColor;
}