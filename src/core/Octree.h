#pragma once

#include "../common.h"

class PointOctree
{
public:
	PointOctree();
	~PointOctree();

	void Clear();

	void AddPoint(glm::vec3& point);

	std::vector<glm::vec3> GetNeighbors(glm::vec3& point);

private:
	std::vector<glm::vec3> m_Points = std::vector<glm::vec3>();
};
