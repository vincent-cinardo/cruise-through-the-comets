#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex;

void main()
{
    vec4 texcolor = texture(tex, texCoord);
    if(texcolor.a < 0.1) discard;
    FragColor = texcolor;
}