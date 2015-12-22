#version 330 core

layout (location = 0) out vec4 gPositionDepth;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 Tangent;

const float NEAR = 0.1;
const float FAR = 1000.0f; 

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));    
}

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform bool useTextures;
uniform bool useNormalMaps;
uniform bool useSpecularMaps;

void main()
{    
    vec4 mainTex = vec4(texture(texture_diffuse1, TexCoords));
    vec4 specTex = vec4(texture(texture_specular1, TexCoords));
    vec4 normTex = vec4(texture(texture_normal1, TexCoords));


    gPositionDepth.xyz = FragPos;
    gPositionDepth.a = LinearizeDepth(gl_FragCoord.z);

    gNormal = normalize(Normal);

    if (useTextures)
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

    if (useNormalMaps)
    {
        vec3 tangent = normalize(Tangent);
        tangent = normalize(tangent - dot(tangent, gNormal) * gNormal);

        vec3 bitangent = cross(tangent, gNormal);

        vec3 BumpMapNormal = normTex.xyz;
        BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);

        vec3 NewNormal;
        mat3 TBN = mat3(tangent, bitangent, gNormal);
        NewNormal = TBN * BumpMapNormal;
        NewNormal = normalize(NewNormal);

        gNormal = NewNormal;
    }

    if (useSpecularMaps)
    {
        // TODO
    }   
}