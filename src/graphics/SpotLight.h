#pragma once

#include "../common.h"

class SpotLight
{
public:
	SpotLight(vec3 pos, vec3 dir) : position(pos), direction(dir) {}

	vec3 position;
	vec3 direction;

	float cutOff = glm::cos(glm::radians(12.5f));
	float outerCutOff = glm::cos(glm::radians(15.0f));

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	vec3 ambient = vec3(0.0f);
	vec3 diffuse = vec3(1.0f);
	vec3 specular = vec3(1.0f);

private:

};