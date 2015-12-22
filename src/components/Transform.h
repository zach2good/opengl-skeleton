#pragma once

class Transform
{
public:
	Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1))
		:m_position(position), m_rotation(rotation), m_scale(scale) {};

	inline void ChangePosition(glm::vec3 position) { m_position += position; }
	inline void ChangeRotation(glm::vec3 rotation) { m_rotation += rotation; }
	inline void ChangeScale(glm::vec3 scale) { m_scale += scale; }

	inline glm::vec3 GetPosition() { return m_position; }
	inline glm::vec3 GetRotation() { return m_rotation; }
	inline glm::vec3 GetScale() { return m_scale; }

	inline void SetPosition(glm::vec3 position) { m_position = position; }
	inline void SetRotation(glm::vec3 rotation) { m_rotation = rotation; }
	inline void SetScale(glm::vec3 scale) { m_scale = scale; }

	inline glm::mat4 GetTransformationMatrix()
	{
		// Create transformation matrix
		glm::mat4 transMatrix = glm::translate(m_position);

		// Create rotation matrix
		glm::mat4 rotMatrix =
			glm::rotate(m_rotation.z, glm::vec3(0, 0, 1)) *
			glm::rotate(m_rotation.y, glm::vec3(0, 1, 0)) *
			glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));

		// Create scale matrix
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		// Return total transform matrix
		return transMatrix * rotMatrix * scaleMatrix;
	}

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

private:

};