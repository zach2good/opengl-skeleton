#include "Octree.h"

PointOctree::PointOctree()
{

}

PointOctree::~PointOctree()
{

}

void PointOctree::Clear()
{
	m_Points.clear();
}

void PointOctree::AddPoint(glm::vec3& point)
{
	m_Points.push_back(point);
}

std::vector<glm::vec3> PointOctree::GetNeighbors(glm::vec3& point)
{
	auto query = std::vector<glm::vec3>();

	return m_Points;
}