#version 330 core

out vec4 FragColor;

in vec3 myColor;
in vec2 texCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float visibility;
uniform float red, blue, green;

void main()
{
    FragColor = mix(vec4(red,green,blue,1.0f) * texture(tex1, texCoord), texture(tex2, vec2(1.0-texCoord.x, texCoord.y)), visibility);
}