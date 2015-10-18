#include "common.h"

class SpotLight
{
public:
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.035f;

	float cutOff = glm::cos(glm::radians(10.0f));
	float outerCutOff = glm::cos(glm::radians(15.0f));

	SpotLight(vec3 pos, vec3 dir, vec3 col = vec3(1.0f))
	{
		position = pos;
		direction = dir;

		ambient = vec3(0.0f) * col;
		diffuse = vec3(1.0f) * col;
		specular = vec3(1.0f) * col;
	}
};