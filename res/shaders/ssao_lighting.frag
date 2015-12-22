#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

struct Light {
    vec3 Position;
    vec3 Color; 
    float Linear;
    float Quadratic;
};
uniform Light light;

uniform int draw_mode;
uniform float ambientLevel;

float LinearizeDepth(float depth)
{
    float NEAR = 0.1f;
    float FAR = 1000.0f;

    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));    
}

void main()
{      
    if (draw_mode == 0) return;

    vec3 FragPos = texture(gPositionDepth, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;

    float Depth = LinearizeDepth(texture(gPositionDepth, TexCoords).a);
    float AmbientOcclusion = texture(ssao, TexCoords).r;
    
    vec3 ambient = Diffuse * AmbientOcclusion * ambientLevel;
    vec3 lighting = ambient; 
    vec3 viewDir = normalize(-FragPos);

    // Diffuse
    vec3 lightDir = normalize(light.Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.Color;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0f);
    vec3 specular = light.Color * spec;

    // Attenuation
    float distance = length(light.Position - FragPos);
    float attenuation = 1.0 / (1.0 + light.Linear * distance + light.Quadratic * distance * distance);
    
    diffuse *= attenuation;
    specular *= attenuation;
    lighting += diffuse + specular;

    switch(draw_mode)
    {
        case 1: FragColor = vec4(lighting, 1.0); break; // Full
        case 2: FragColor = vec4(FragPos, 1.0); break; // Position
        case 3: FragColor = vec4(Normal, 1.0); break; // Normals
        case 4: FragColor = vec4(Diffuse, 1.0); break; // Diffuse
        case 5: FragColor = vec4(vec3(Depth), 1.0); break; // Depth
        case 6: FragColor = vec4(diffuse + specular, 1.0); break; // Phong
        case 7: FragColor = vec4(vec3(1.0f) * AmbientOcclusion, 1.0); break; // AO
    }
    
}