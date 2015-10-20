#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 color;

void main()
{
	// Properties
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Diffuse shading
    float diff = max(dot(normal, viewDir), 0.0);

	// Specular shading
    vec3 reflectDir = reflect(-viewDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	// Result
	float lighting = (diff + spec);

	// Out
    FragColor = vec4(color * lighting, 1.0f);
}