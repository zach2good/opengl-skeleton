#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

const int NR_LIGHTS = 2;
struct Light {
    int Type;

    vec3 Position;
    vec3 Color; 

    float Constant;
    float Linear;
    float Quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 Direction;
    float CutOff;
    float OuterCutOff;
};
uniform Light lights[NR_LIGHTS];

uniform int draw_mode;
uniform float ambientLevel;

void main()
{      
    // NOOP
    if (draw_mode == 0) return;

    vec3 FragPos = texture(gPositionDepth, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;
    float Depth = texture(gPositionDepth, TexCoords).a;
    float AmbientOcclusion = texture(ssao, TexCoords).r;
    
    vec3 ambient = Diffuse * AmbientOcclusion * ambientLevel;
    vec3 lighting = ambient; 
    vec3 viewDir  = normalize(-FragPos);

    vec3 phongResult;
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // Diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;

        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = lights[i].Color * spec ;

        // Attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (lights[i].Constant + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);

        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;

        phongResult += diffuse + specular;
    } 

    switch(draw_mode)
    {
        case 1: FragColor = vec4(lighting, 1.0); break; // Full
        case 2: FragColor = vec4(FragPos, 1.0); break; // Position
        case 3: FragColor = vec4(Normal, 1.0); break; // Normals
        case 4: FragColor = vec4(Diffuse, 1.0); break; // Diffuse
        case 5: FragColor = vec4(vec3(Depth / 100), 1.0); break; // Depth
        case 6: FragColor = vec4(phongResult, 1.0); break; // Phong
        case 7: FragColor = vec4(vec3(1.0f) * AmbientOcclusion, 1.0); break; // AO
    }
}