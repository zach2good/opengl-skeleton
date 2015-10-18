#include "common.h"

class DirLight 
{
public:
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	DirLight(vec3 dir, vec3 col = vec3(1.0f))
	{
		direction = dir;

		ambient = vec3(0.05f) * col;
		diffuse = vec3(0.4f) * col;
		specular = vec3(0.5f) * col;
	}
};