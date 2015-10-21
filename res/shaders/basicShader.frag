#version 330 core

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  
	
	float cutOff;
    float outerCutOff;     
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;
uniform float shininess;

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform bool useNormalMapping;

uniform bool showNormalMap;
uniform bool showSpecularMap;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{   
	// Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	if (useNormalMapping)
	{
		// Obtain normal from normal map
		norm = texture(normalMap, TexCoords).rgb;

		// Transform normal vector to range [-1,1]
		norm = normalize(norm * 2.0 - 1.0); 
	} 

	vec3 dir = CalcDirLight(dirLight, norm, viewDir);
	vec3 point = CalcPointLight(pointLight, norm, FragPos, viewDir); 
	vec3 spot = CalcSpotLight(spotLight, norm, FragPos, viewDir); 

	vec3 result = dir + point + spot;

	if (showSpecularMap) 
	{
		result = vec3(texture(specularMap, TexCoords));
	}

	if (showNormalMap) 
	{
		result = vec3(texture(normalMap, TexCoords));
	}

    color = vec4(result, 1.0);
} 

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(diffuseMap, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularMap, TexCoords));

    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
	   
    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(diffuseMap, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularMap, TexCoords));

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
	   
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Combine results
    vec3 ambient  = light.ambient  * vec3(texture(diffuseMap, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseMap, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(specularMap, TexCoords));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}