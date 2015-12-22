#version 330 core
layout (location = 0) out vec4 gPositionDepth;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

const float NEAR = 0.1; // Projection matrix's near plane distance
const float FAR = 1000.0f; // Projection matrix's far plane distance

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));    
}

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform bool hasTextures;

void main()
{    
    vec4 mainTex = vec4(texture(texture_diffuse1, TexCoords));
    vec4 specTex = vec4(texture(texture_specular1, TexCoords));
    vec4 normTex = vec4(texture(texture_normal1, TexCoords));

    // Store the fragment position vector in the first gbuffer texture
    gPositionDepth.xyz = FragPos;

    // And store linear depth into gPositionDepth's alpha component
    gPositionDepth.a = LinearizeDepth(gl_FragCoord.z);

    // Also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);

    // Geometry color, white if no textures loaded
    if (hasTextures)
    {
		gAlbedoSpec.rgb = mainTex.rgb;

		if (mainTex.a < 0.1f)
		{
			discard;
		}
    }
    else
    {
     	gAlbedoSpec.rgb = vec3(1.0f);
    }
   
}