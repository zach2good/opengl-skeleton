#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;
uniform vec3 lightPosition;

void main()
{
	vec4 worldPosition = model * vec4(normal, 0.0);
	vec4 positionRelativeToCam = view * worldPosition;

    gl_Position = projection * view * model * vec4(position, 1.0f);

	Position = vec3(model * vec4(position, 1.0f));
	Normal = (model * vec4(normal, 0.0)).xyz;
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}