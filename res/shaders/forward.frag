#version 330 core

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

in vec3 ViewPos;

out vec4 color;

uniform sampler2D texture_0;

void main()
{
    color = texture(texture_0, TexCoord);
} 