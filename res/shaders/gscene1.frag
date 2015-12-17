#version 330 core

#define RAZZAMATAZZ vec3(0.89f, 0.145f, 0.42f)
#define FIREBRICK vec3(0.698f, 0.133f, 0.133f)
#define WHITE vec3(1.0f, 1.0f, 1.0f)
#define BLACK vec3(0.0f, 0.0f, 0.0f)

const float gamma = 2.2;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color_out;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform int hasTextures;

void main()
{
    vec4 mainTex = vec4(texture(texture_diffuse1, TexCoords));

    vec3 objectColor = WHITE;

    if (mainTex.a < 0.1f && hasTextures > 0)
    {
        discard;
    }

    if (hasTextures > 0)
    {
        objectColor = vec3(mainTex);
    }

    vec3 lightColor = WHITE;

    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.9f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor * vec3(texture(texture_specular1, TexCoords));

    // Linear result     
    vec3 result = (ambient + diffuse + specular) * objectColor;

    // Gamma
    result = pow(result, vec3(1.0/gamma));
    color_out = vec4(result, 1.0f);
}