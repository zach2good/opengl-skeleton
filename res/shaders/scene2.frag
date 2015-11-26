#version 330 core
in vec2 TexCoord;
in vec3 vsColor;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;

void main()
{	
	vec4 c = vec4(vsColor, 1.0f);
	color = texture(ourTexture1, TexCoord) * c;
}