#include "common.h"

class PointLight
{
public:
	vec3 position;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.035f;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	PointLight(vec3 pos, vec3 col = vec3(1.0f))
	{
		position = pos;

		ambient = vec3(0.1f) * col;
		diffuse = vec3(0.7f) * col;
		specular = vec3(1.0f) * col;
	}
};