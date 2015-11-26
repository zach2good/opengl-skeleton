#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 Tangent;
    vec3 Bitangent;
    mat3 TBN;
} fs_in;

out vec4 FragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 viewPos;
uniform vec3 lightPos;

void main()
{
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;

    // Ambient
    vec3 ambient = 0.05 * color;

    // Diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);

    vec3 normal = normalize(fs_in.Normal);

    // Normal Mapping
    normal = texture(normalMap, fs_in.TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0); 
    normal = normalize(fs_in.TBN * normal); 

    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    // Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.3) * spec; // assuming bright white light color

    vec4 result = vec4(ambient + diffuse + specular, 1.0f);

    FragColor = result;
}
