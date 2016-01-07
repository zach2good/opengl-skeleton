#include "Octree.h"

Octree::Octree(const glm::vec3& origin, const glm::vec3& halfDimension) :
	m_Origin(origin),
	m_HalfDimension(halfDimension),
	m_Data(NULL),
	m_Parent(NULL)
{
	for (int i = 0; i < 8; ++i)
	{
		m_Children[i] = NULL;
	}
}

Octree::Octree(const Octree& copy) :
	m_Origin(copy.m_Origin),
	m_HalfDimension(copy.m_HalfDimension),
	m_Data(copy.m_Data) { }

Octree::~Octree()
{
	for (int i = 0; i < 8; ++i)
	{
		delete m_Children[i];
	}
}

int Octree::GetOctantContainingGameObject(const GameObject & go) const
{
	int oct = 0;

	glm::vec3 point = go.m_Transform.m_position;

	if (point.x >= m_Origin.x) oct |= 4;
	if (point.y >= m_Origin.y) oct |= 2;
	if (point.z >= m_Origin.z) oct |= 1;

	return oct;
}

bool Octree::IsTopLevel() const
{
	return m_Parent == NULL;
}

bool Octree::IsLeafNode() const
{
	return m_Children[0] == NULL;
}

void Octree::Insert(GameObject* point)
{
	if (IsLeafNode())
	{
		if (m_Data == NULL)
		{
			m_Data = point;
			return;
		}
		else
		{
			GameObject *oldPoint = m_Data;
			m_Data = NULL;
			m_Parent = this;

			for (int i = 0; i < 8; ++i)
			{
				glm::vec3 newOrigin = m_Origin;

				newOrigin.x += m_HalfDimension.x * (i & 4 ? .5f : -.5f);
				newOrigin.y += m_HalfDimension.y * (i & 2 ? .5f : -.5f);
				newOrigin.z += m_HalfDimension.z * (i & 1 ? .5f : -.5f);

				m_Children[i] = new Octree(newOrigin, m_HalfDimension * 0.5f);
			}

			m_Children[GetOctantContainingGameObject(*oldPoint)]->Insert(oldPoint);
			m_Children[GetOctantContainingGameObject(*point)]->Insert(point);
		}
	}
	else
	{
		int octant = GetOctantContainingGameObject(*point);
		m_Children[octant]->Insert(point);
	}
}

void Octree::Clear()
{
	if (IsLeafNode())
	{
		delete this;
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			m_Children[i]->Clear();
		}
	}
}

void Octree::GetGameObjectsInsideBox(const glm::vec3 & bmin, const glm::vec3 & bmax, std::vector<GameObject*>& results)
{
	if (IsLeafNode())
	{
		if (m_Data != NULL)
		{
			const glm::vec3& p = m_Data->m_Transform.m_position;

			if (p.x > bmax.x || p.y > bmax.y || p.z > bmax.z) return;
			if (p.x < bmin.x || p.y < bmin.y || p.z < bmin.z) return;

			results.push_back(m_Data);
		}
	}
	else
	{
		for (int i = 0; i < 8; ++i)
		{
			glm::vec3 cmax = m_Children[i]->m_Origin + m_Children[i]->m_HalfDimension;
			glm::vec3 cmin = m_Children[i]->m_Origin - m_Children[i]->m_HalfDimension;

			if (cmax.x < bmin.x || cmax.y < bmin.y || cmax.z < bmin.z) continue;
			if (cmin.x > bmax.x || cmin.y > bmax.y || cmin.z > bmax.z) continue;

			m_Children[i]->GetGameObjectsInsideBox(bmin, bmax, results);
		}
	}
}
