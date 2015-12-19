#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

uniform float time;
uniform float width;
uniform float height;

const float offset = 1.0 / 500;  

vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );

float kernel1[9] = float[](
        -1,  0, 1,
        -2,  0, 2,
        -1,  0, 1
    );

float kernel2[9] = float[](
        -1, -2, -1,
         0,  0,  0,
         1,  2,  1
    );

void main()
{
    vec3 sampleTex[9];

    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel1[i];
    }

    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel2[i];
    }

    if ((col.x < 0.0f) || (col.y < 0.0f) || (col.z < 0.0f))
    {
    	discard;
    }
    
    color = vec4(col, 1.0);
}  