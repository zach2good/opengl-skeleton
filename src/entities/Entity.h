#pragma once

#include <graphics\models\Mesh.h>
#include <entities\Transformation.h>

class Entity
{
public:
	Entity(Mesh mesh, Transformation tran)
		: m_Mesh(mesh), m_Transformation(tran) {}

	Transformation m_Transformation;
	Mesh m_Mesh;
};