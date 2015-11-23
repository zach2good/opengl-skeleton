#pragma once

#include "../common.h"
#include "../components/Transformation.h"
#include "Mesh.h"

class Entity
{
public:
	Entity(Mesh* m) : mesh(m) {};

	Mesh* mesh;
	Transformation trans;
};