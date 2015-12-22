#pragma once

class Transform
{
public:
	Transform(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1))
		:m_position(position), m_rotation(rotation), m_scale(scale) {};

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

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



private:

};