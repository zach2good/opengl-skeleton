#version 330 core

#define RAZZAMATAZZ vec3(0.89f, 0.145f, 0.42f)
#define FIREBRICK vec3(0.698f, 0.133f, 0.133f)

#define WHITE vec3(1.0f, 1.0f, 1.0f)
#define LIGHT_GRAY vec3(0.749f, 0.749f, 0.749f)
#define GRAY vec3(0.498f, 0.498f, 0.498f)
#define DARK_GRAY vec3(0.247f, 0.247f, 0.247f)
#define SLATE vec3(0.439f, 0.502f, 0.565f)
#define BLACK vec3(0.0f, 0.0f, 0.0f)

const float gamma = 2.2; 
const vec3 ambientColor = vec3(0.1, 0.0, 0.0);
const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color_out;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{    
    vec3 lightColor = WHITE;
    vec3 objectColor = FIREBRICK;

     // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 2.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
     
    // Linear result   
    vec3 result = (ambient + diffuse + specular) * objectColor;   

    // Gamma
    vec3 gammaCorrected = pow(result, vec3(1.0/gamma));
    color_out = vec4(gammaCorrected, 1.0f);
}