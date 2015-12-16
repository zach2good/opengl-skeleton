#pragma once

#include "../common.h"

#include "../components/Transform.h"
#include "../graphics/Mesh.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	Transform m_Transform;
	Mesh* m_Mesh = nullptr;

	bool isLight = false;

private:

};