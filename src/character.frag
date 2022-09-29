#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D image;

void main()
{
    vec4 texcolor = texture(image, texCoord);
    //vec4 texcolor = vec4(0.2, 0.5, 0.8, 1.0f);
    if(texcolor.a < 0.1) discard;
    FragColor = texcolor;
}