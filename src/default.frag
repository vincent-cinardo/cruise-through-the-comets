#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in float texInd;

uniform sampler2D tex[2]; //Put both textures in here, then use texture function on frag color

void main()
{
    //vec4 texcolor = texture(tex, texCoord);
    vec4 texcolor = vec4(texCoord.x, texCoord.y, texCoord.x, 1.0f);
    //if(texcolor.a < 0.1) discard;
    FragColor = texcolor;
}