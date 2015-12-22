#pragma once

#include "../common.h"
#include "../core/Component.h"
#include "../components/Transform.h"
#include "../graphics/Model.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::string name) : m_Name(name) {};
	~GameObject();

	void Update();

	std::string m_Name;
	int m_Id;
	Transform m_Transform;
	Model* m_Model = nullptr;
	bool isLight = false;

private:
	std::vector<GameObject*> m_Children;
	std::vector<Component*> m_Components;

};