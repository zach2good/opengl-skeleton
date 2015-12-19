#pragma once

#include "../common.h"

class PointLight
{
public:
	PointLight(vec3 pos) : position(pos) {}

	vec3 position;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	vec3 ambient = vec3(0.05f);
	vec3 diffuse = vec3(0.8f);
	vec3 specular = vec3(1.0f);
};