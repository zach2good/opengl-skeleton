#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec3 FragPos; 
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view *  model * vec4(position, 1.0f);

	FragPos = vec3(model * vec4(position, 1.0f));
	TexCoords = texCoords;  
    Normal = mat3(transpose(inverse(model))) * normal; 

} 