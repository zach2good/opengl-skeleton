#version 330 core

// In
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 texCoord;
layout (location = 2) in vec3 normal;

// Out
out vec2 TexCoord;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

// Matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Lights
uniform vec3 lightPosition;

// Material
uniform vec3 color;
uniform float shineDamper;
uniform float reflectivity;


void main()
{
	vec4 worldPosition = model * vec4(normal, 0.0);
	vec4 positionRelativeToCam = view * worldPosition;

    gl_Position = projection * view * model * vec4(position, 1.0f);

	// Pass
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
	surfaceNormal = (model * vec4(normal, 0.0)).xyz;
	toLightVector = lightPosition - worldPosition.xyz;
	toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
} 