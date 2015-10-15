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

float near = 1.0; 
float far  = 100.0; 
  
float Linearize(float target) 
{
    float z = target * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

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

	// Depth
	float depthCol = Linearize(gl_FragCoord.z) / far; 
    vec4 DepthFragColor = vec4(vec3(depthCol), 1.0f);

	// Normal
	float normalCol = Linearize(gl_FragCoord.z) / far; 
    vec4 NormalFragColor = vec4(vec3(unitNormal), 1.0f);

	// Texture + Lighting
    vec4 GeomColor = vec4(diffuse, 1.0) * texture2D(texture0, TexCoord) + vec4(finalSpecular, 1.0);

	if (gl_FragCoord.x < 500)
	{
		FragColor = GeomColor;
	}
	else if (gl_FragCoord.x < 800)
	{
		 FragColor = NormalFragColor ;
	}
	else
	{
		FragColor = DepthFragColor;
	}	
}