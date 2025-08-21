#include "Core/InputManager.hpp"
#include <iostream>


using namespace Engine::Core;

InputManager::InputManager(GLFWwindow* window)
	: m_window(window){}

void InputManager::Update()
{
	for (auto& [actionType, action] : keyBinds) {
		action.m_isPressed = IsKeyPressed(action.m_key);
		action.m_isReleased = IsKeyReleased(action.m_key);
		action.m_isKeyHeld = IsKeyHeld(action.m_key);
	}
	
}




bool InputManager::IsActionPressed(m_ActionType action) const
{
	return keyBinds.at(action).m_isPressed;
}
bool InputManager::IsActionReleased(m_ActionType action) const
{
	return keyBinds.at(action).m_isReleased;
}
bool InputManager::IsActionHeld( m_ActionType action) const
{
	return keyBinds.at(action).m_isKeyHeld;
}

bool InputManager::IsKeyPressed(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}
bool InputManager::IsKeyReleased(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_RELEASE;
}
bool InputManager::IsKeyHeld(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}


bool InputManager::IsMouseButtonPressed(int button) const
{
	return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}
bool InputManager::IsMouseButtonReleased(int button) const
{
	return glfwGetMouseButton(m_window, button) == GLFW_RELEASE;
}
bool InputManager::IsMouseButtonHeld(int button) const
{
	return glfwGetMouseButton(m_window, button) == GLFW_REPEAT;
}


void InputManager::GetMousePosition(double& x, double& y) const
{
	glfwGetCursorPos(m_window, &x, &y);
}
void InputManager::SetMousePosition(double x, double y)
{
	glfwSetCursorPos(m_window, x, y);
}
void InputManager::SetWindow(void* window)
{
	m_window = static_cast<GLFWwindow*>(window);
}

