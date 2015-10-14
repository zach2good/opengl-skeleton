#version 330 core

// In
in vec2 TexCoord;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

// Output
out vec4 FragColor;

// Texture sampler
uniform sampler2D texture;

// Light
uniform vec3 lightColor;

// Material
uniform vec3 color;
uniform float shineDamper;
uniform float reflectivity;


void main()
{
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.0);
	vec3 diffuse = brightness *  lightColor * color;

	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
	specularFactor = max(specularFactor, 0.15);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;


	FragColor = vec4(diffuse, 1.0) * texture2D(texture, TexCoord) + vec4(finalSpecular, 1.0);
}