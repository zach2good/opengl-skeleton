#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;

void main()
{
	color = vec4(vec3(texture(ourTexture1, TexCoords)), 1.0f);
}