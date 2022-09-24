#version 330 core

in vec2 aTextureCoord;

uniform sampler2D image;

out vec4 FragColor;

void main()
{
	vec4 texColor = texture(image, aTextureCoord);
	FragColor = texColor;
}