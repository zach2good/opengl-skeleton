#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 FragColor;

uniform sampler2D texture0;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
	vec3 unitNormal = normalize(Normal);
	vec3 unitLightVector = normalize(toLightVector); 

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.0);

	vec3 diffuse = brightness *  lightColor;

	vec3 unitVectorToCamera = normalize(toCameraVector);
	vec3 lightDirection = -unitLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

	float shineDamper = 0.15f;
	float reflectivity = 0.15f;
	float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
	specularFactor = max(specularFactor, 0.15);
	float dampedFactor = pow(specularFactor, shineDamper);
	vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

	// Texture + Lighting
    FragColor = vec4(diffuse, 1.0) * texture2D(texture0, TexCoord) + vec4(finalSpecular, 1.0);
}