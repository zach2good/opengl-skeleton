#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 tangent;
layout (location = 4) in vec2 bitangent;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

out mat3 TBN;

out vec3 ViewPos;

uniform mat4 model;
uniform mat4 view;
uniform vec3 viewPos;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);


	Position = position;
	Normal = normal;
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

	ViewPos = viewPos;

	//mat3 normalMatrix = transpose(inverse(mat3(model)));
	//Normal = normalMatrix * normal;

	//vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
    //vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    //vec3 N = normalize(vec3(model * vec4(normal,    0.0)));
	//mat3 TBN = transpose(mat3(T, B, N));     
}