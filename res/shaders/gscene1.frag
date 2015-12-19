#version 330 core

#define RAZZAMATAZZ vec3(0.89f, 0.145f, 0.42f)
#define FIREBRICK vec3(0.698f, 0.133f, 0.133f)
#define WHITE vec3(1.0f, 1.0f, 1.0f)
#define BLACK vec3(0.0f, 0.0f, 0.0f)

const float gamma = 2.2;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

out vec4 color_out;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform int hasTextures;

void main()
{
    vec3 lightColor = WHITE;

    vec4 mainTex = vec4(texture(texture_diffuse1, TexCoords));
    vec4 specTex = vec4(texture(texture_specular1, TexCoords));
    vec4 normTex = vec4(texture(texture_normal1, TexCoords));

    vec3 objectColor = WHITE;

    // Deal with alpha
    if (hasTextures > 0)
    {
        objectColor = vec3(mainTex);
        
        if (mainTex.a < 0.1f)
        {
            discard;
        }
    }  

    // Linear result     
    vec3 result = objectColor;

    // Gamma
    //result = pow(result, vec3(1.0/gamma));
    color_out = mainTex; //vec4(result, 1.0f);
}