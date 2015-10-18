#version 330 core

in vec3 Normal;

out vec4 FragColor;

uniform vec3 color;

void main()
{
    FragColor = vec4(color + (Normal * 0.2f), 1.0f);
}