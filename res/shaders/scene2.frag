#version 330 core
in vec2 TexCoord;
in vec3 vsColor;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{	
	vec4 c = vec4(vsColor, 1.0f);
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}