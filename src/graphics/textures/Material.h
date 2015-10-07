#pragma once

#include <glm/glm.hpp>
#include <graphics\textures\Texture.h>

struct Material
{
public:
	Material(Texture t, glm::vec3 c = glm::vec3(1.0f, 1.0f, 1.0f))
		: m_Texture(t), m_Color(c) {}

	Texture m_Texture;
	glm::vec3 m_Color;
	float m_SpecularIntensity;
	float m_SpecularExponent;
};
