#pragma once

#include "../common.h"
#include "GameObject.h"

class Octree
{
public:
	Octree(const glm::vec3& origin, const glm::vec3& halfDimension);
	Octree(const Octree& copy);
	~Octree();

	int GetOctantContainingGameObject(const GameObject& go) const;

	bool IsLeafNode() const;

	bool IsTopLevel() const;

	void Insert(GameObject* go);

	void Clear();

	void GetGameObjectsInsideBox(const glm::vec3& bmin, const glm::vec3& bmax, std::vector<GameObject*>& results);

private:
	glm::vec3 m_Origin;
	glm::vec3 m_HalfDimension;

	int depth = 0;
	int maxDepth = 5;

	Octree* m_Parent;
	std::vector<Octree*> m_Children;

	GameObject* m_Data;


};