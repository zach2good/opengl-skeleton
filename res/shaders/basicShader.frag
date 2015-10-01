#version 330 core

in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D texture;

void main()
{
	color = texture(texture, TexCoord);
}