#pragma once

#include "../common.h"

class DirectionalLight
{
public:
	DirectionalLight(vec3 dir) : direction(dir) {}

	vec3 direction;

	vec3 ambient = vec3(0.05f);
	vec3 diffuse = vec3(0.4f);
	vec3 specular = vec3(0.5f);

private:

};