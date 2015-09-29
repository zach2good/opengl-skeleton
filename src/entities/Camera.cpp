#include "Camera.h"

#include <SDL.h>

#include <glm\gtx\transform.hpp>

Camera::Camera()
	: m_position(glm::vec3(0, 5, 0))
{

}


Camera::~Camera()
{
}


void Camera::Update()
{
	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F6) == GLFW_PRESS)
	//{
	//	if (m_wireframe)
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//	else
	//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//	m_wireframe = !m_wireframe;
	//}
}


glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}