#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
    mat3 TBN;
} fs_in;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;

void main()
{
	color = texture(ourTexture1, fs_in.TexCoords);
}