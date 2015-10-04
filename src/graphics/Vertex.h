#pragma once

#include <glm/glm.hpp>

struct Vertex
{
public:
	int Size = 15;
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
	glm::vec3 Tangent;
};
