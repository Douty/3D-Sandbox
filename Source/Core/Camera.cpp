#include "Core/Camera.hpp"

using namespace Engine::Core;
	
Camera::Camera() : m_Position(glm::vec3(0.0f, 0.0f, 3.0f)),
m_Forward(glm::vec3(0.0f, 0.0f, -1.0f)), m_Right(glm::vec3(1.0f, 0.0f, 0.0f)),
m_Up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}
Camera::Camera(glm::vec3 position, glm::vec3 forward, 
	glm::vec3 right, glm::vec3 up) : m_Position(position),
	m_Forward(forward), m_Right(right), m_Up(up){}

void Engine::Core::Camera::UpdateProjectionMatrix(float fov, float width, float height, float nearPlane, float farPlane)
{
	m_Projection = glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
}


void Engine::Core::Camera::UpdateViewMatrix()
{
	CalculateDirection();
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}



void Engine::Core::Camera::CalculateDirection() {
	glm::vec3 direction{};
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_Forward = glm::normalize(direction);

	const glm::vec3 worldUp(0.0f, 1.0f, 0.0f);

	m_Right = glm::normalize(glm::cross(m_Forward, worldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}



