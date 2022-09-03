#version 330 core

out vec4 FragColor;

in vec2 text;

uniform sampler2D aText;

void main()
{
	FragColor = texture(aText, text);
}

