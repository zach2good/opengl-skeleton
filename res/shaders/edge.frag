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

vec3 grey(vec3 color_in)
{
  vec3 colorG = color_in;

  float grey = dot(colorG, vec3(0.299, 0.587, 0.114));

  colorG = colorG * grey;

  return colorG;
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

float luma(vec3 color) {
  return dot(color, vec3(0.299, 0.587, 0.114));
}

float luma(vec4 color) {
  return dot(color.rgb, vec3(0.299, 0.587, 0.114));
}

float dither8x8(vec2 position, float brightness) {
  int x = int(mod(position.x, 8.0));
  int y = int(mod(position.y, 8.0));
  int index = x + y * 8;
  float limit = 0.0;

  if (x < 8) {
    if (index == 0) limit = 0.015625;
    if (index == 1) limit = 0.515625;
    if (index == 2) limit = 0.140625;
    if (index == 3) limit = 0.640625;
    if (index == 4) limit = 0.046875;
    if (index == 5) limit = 0.546875;
    if (index == 6) limit = 0.171875;
    if (index == 7) limit = 0.671875;
    if (index == 8) limit = 0.765625;
    if (index == 9) limit = 0.265625;
    if (index == 10) limit = 0.890625;
    if (index == 11) limit = 0.390625;
    if (index == 12) limit = 0.796875;
    if (index == 13) limit = 0.296875;
    if (index == 14) limit = 0.921875;
    if (index == 15) limit = 0.421875;
    if (index == 16) limit = 0.203125;
    if (index == 17) limit = 0.703125;
    if (index == 18) limit = 0.078125;
    if (index == 19) limit = 0.578125;
    if (index == 20) limit = 0.234375;
    if (index == 21) limit = 0.734375;
    if (index == 22) limit = 0.109375;
    if (index == 23) limit = 0.609375;
    if (index == 24) limit = 0.953125;
    if (index == 25) limit = 0.453125;
    if (index == 26) limit = 0.828125;
    if (index == 27) limit = 0.328125;
    if (index == 28) limit = 0.984375;
    if (index == 29) limit = 0.484375;
    if (index == 30) limit = 0.859375;
    if (index == 31) limit = 0.359375;
    if (index == 32) limit = 0.0625;
    if (index == 33) limit = 0.5625;
    if (index == 34) limit = 0.1875;
    if (index == 35) limit = 0.6875;
    if (index == 36) limit = 0.03125;
    if (index == 37) limit = 0.53125;
    if (index == 38) limit = 0.15625;
    if (index == 39) limit = 0.65625;
    if (index == 40) limit = 0.8125;
    if (index == 41) limit = 0.3125;
    if (index == 42) limit = 0.9375;
    if (index == 43) limit = 0.4375;
    if (index == 44) limit = 0.78125;
    if (index == 45) limit = 0.28125;
    if (index == 46) limit = 0.90625;
    if (index == 47) limit = 0.40625;
    if (index == 48) limit = 0.25;
    if (index == 49) limit = 0.75;
    if (index == 50) limit = 0.125;
    if (index == 51) limit = 0.625;
    if (index == 52) limit = 0.21875;
    if (index == 53) limit = 0.71875;
    if (index == 54) limit = 0.09375;
    if (index == 55) limit = 0.59375;
    if (index == 56) limit = 1.0;
    if (index == 57) limit = 0.5;
    if (index == 58) limit = 0.875;
    if (index == 59) limit = 0.375;
    if (index == 60) limit = 0.96875;
    if (index == 61) limit = 0.46875;
    if (index == 62) limit = 0.84375;
    if (index == 63) limit = 0.34375;
  }

  return brightness < limit ? 0.0 : 1.0;
}

vec3 dither8x8(vec2 position, vec3 color) {
  return color * dither8x8(position, luma(color));
}

vec4 dither8x8(vec2 position, vec4 color) {
  return vec4(color.rgb * dither8x8(position, luma(color)), 1.0);
}

void main()
{
    // Get UV
    vec2 texCoords = TexCoords;

    // UV Effects
    texCoords = wave(texCoords, time, 0.05, 10);
    texCoords = pixel(texCoords);

    // Get Color
    //vec3 col = texture2D(screenTexture, texCoords).rgb;

    // Edge Detection
    //col = edge(screenTexture, texCoords);

    // Greyscale
    //col = grey(col);

    // Color Effects
    //col = gameboy(col);

    vec4 col4 = texture2D(screenTexture, texCoords);

    col4 = dither8x8(gl_FragCoord.xy, texture2D(screenTexture, texCoords)) * 2.0;

    // Output
    color = texture2D(screenTexture, TexCoords);
    color = vec4(gameboy(col4.rgb), 1.0f);
}  
