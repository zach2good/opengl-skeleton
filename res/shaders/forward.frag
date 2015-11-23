#version 330 core

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

in vec3 ViewPos;

out vec4 color;

uniform sampler2D texture_0;

void main()
{
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ViewPos - Position);

	// Diffuse shading
    float diff = max(dot(norm, viewDir), 0.0);
	vec4 col = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    color = vec4(texture(texture_0, TexCoord));
} 