#pragma once

#include "../common.h"

#include "../components/Transformation.h"
#include "../graphics/Mesh.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transformation m_Transform;
	Mesh m_Mesh = Mesh("../res/models/cube.obj");

private:

};