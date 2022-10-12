#version 330 core

out vec4 FragColor;

in vec2 texCoords;

//Could make this sampler an array of images, to account for more than one asteroid texture.
uniform sampler2D image;

void main()
{
	vec4 texcolor = texture(image, texCoords);
	FragColor = texcolor;
}