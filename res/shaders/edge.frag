#version 330 core

// Some shaders from:
// http://clemz.io/article-retro-shaders-rayman-legends

in vec2 TexCoords;

out vec4 color;

uniform sampler2D screenTexture;

uniform float time;
uniform float width;
uniform float height;

vec2 wave(vec2 tx, float pTime, float A, float f)
{
    vec2 tex = tx;

    float sin_time = pTime / 1000.0f;
    tex.x += A * sin(tex.y * f + sin_time);

    return tex;
}

vec2 pixel(vec2 tx)
{
    vec2 tex = tx;

    float dx = 10.0f * (1.0f/1000.0f);
    float dy = 10.0f * (1.0f/1000.0f);

    vec2 coord = vec2(dx*floor(tex.x/dx), dy*floor(tex.y/dy));

    return coord;
}

vec3 gameboy(vec3 color_in)
{
  vec3 colorGB = color_in;

  float gamma = 1.5;
  colorGB.r = pow(colorGB.r, gamma);
  colorGB.g = pow(colorGB.g, gamma);
  colorGB.b = pow(colorGB.b, gamma);

  vec3 col1 = vec3(0.612, 0.725, 0.086);
  vec3 col2 = vec3(0.549, 0.667, 0.078);
  vec3 col3 = vec3(0.188, 0.392, 0.188);
  vec3 col4 = vec3(0.063, 0.247, 0.063);

  float dist1 = length(colorGB - col1);
  float dist2 = length(colorGB - col2);
  float dist3 = length(colorGB - col3);
  float dist4 = length(colorGB - col4);

  float d = min(dist1, dist2);
  d = min(d, dist3);
  d = min(d, dist4);

  if (d == dist1) {
    colorGB = col1;
  }    
  else if (d == dist2) {
    colorGB = col2;
  }    
  else if (d == dist3) {
    colorGB = col3;
  }    
  else {
    colorGB = col4;
  } 

  return colorGB;
}

vec3 edge(sampler2D in_screenTexture, vec2 in_texcoord)
{
    float offset = 1.0 / 250; 

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

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(in_screenTexture, in_texcoord.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    return col;
}


void main()
{
    // Get UV
    vec2 texCoords = TexCoords;

    // UV Effects
    texCoords = wave(texCoords, time, 0.05, 10);
    texCoords = pixel(texCoords);

    // Get Color
    vec3 col = texture2D(screenTexture, texCoords).rgb;

    // Edge Detection
    col = edge(screenTexture, texCoords);

    // Color Effects
    col = gameboy(col);

    // Output
    color = vec4(col, 1.0);
}  
