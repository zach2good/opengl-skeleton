#version 330 core

out float FragColor;
in vec2 TexCoords;

uniform sampler2D finalColorBuffer;

void main()
{   
    FragColor = texture(finalColorBuffer, TexCoords);
}