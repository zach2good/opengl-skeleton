#pragma once

#include "../common.h"
#include "../core/Component.h"
#include "../components/Transform.h"
#include "../graphics/Model.h"

struct PointLight
{

};

struct DirectionalLight
{

};

struct SpotLight
{

};

class GameObject
{
public:
	GameObject();
	GameObject(std::string name) : m_Name(name) {};
	~GameObject();

	void Update();
	void AddChild(GameObject* go);

	std::string m_Name;
	int m_Id;
	Transform m_Transform;
	Model* m_Model = nullptr;
	
	PointLight* m_PointLight = nullptr;
	DirectionalLight* m_DirectionalLight = nullptr;
	SpotLight* m_SpotLight = nullptr;

private:
	std::vector<GameObject*> m_Children;
	std::vector<Component*> m_Components;
};