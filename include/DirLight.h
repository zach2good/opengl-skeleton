#include "common.h"

class DirLight 
{
public:
	vec3 direction;

	vec3 ambient = vec3(0.05f);
	vec3 diffuse = vec3(0.4f);
	vec3 specular = vec3(0.5f);

	DirLight(vec3 dir)
	{
		direction = dir;
	}
};