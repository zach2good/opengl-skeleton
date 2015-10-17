#include "common.h"

class PointLight
{
public:
	vec3 position;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.035f;

	vec3 ambient = vec3(0.1f);
	vec3 diffuse = vec3(0.7f);
	vec3 specular = vec3(1.0f);

	PointLight(vec3 pos)
	{
		position = pos;
	}
};