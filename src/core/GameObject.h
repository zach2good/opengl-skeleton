#pragma once

#include "../common.h"
#include "../core/Component.h"
#include "../components/Transform.h"
#include "../graphics/Model.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();

	Transform m_Transform;
	Model* m_Model = nullptr;

	// Light m_Light = nullptr;
	bool isLight = false;

private:
	std::vector<GameObject*> m_Children;
	std::vector<Component*> m_Components;

};