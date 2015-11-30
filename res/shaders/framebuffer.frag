#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

uniform float time;
uniform float width;
uniform float height;

void main()
{
    color = texture(screenTexture, TexCoords);
}  