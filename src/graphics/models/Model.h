#pragma once


#include <GL\glew.h>
#include <graphics\models\Mesh.h>
#include <graphics\textures\Material.h>

class Model
{
public:
	Model(Mesh mesh, Material mat)
		: m_Mesh(mesh), m_Material(mat) {}

	Mesh m_Mesh;
	Material m_Material;
};