#include "Core/FirstPersonController.hpp"
#include <iostream>

using namespace Engine::Core;

FirstPersonController::FirstPersonController(Camera& camera, InputManager& input) : m_Camera(camera), m_Input(input)
{
	
}

void FirstPersonController::Update(float deltaTime)
{
	m_Input.Update();
	CameraMovement();
	CameraMouseMovement(deltaTime);

}

void FirstPersonController::CameraMovement()
{
    // Instead of switching on the type itself, check each action using InputManager's methods
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveForward)) {
        std::cout << "Moving Forward" << std::endl;
        m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetForward() * m_Camera.GetSpeed());
    }
    // Add other movement directions as needed:
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveBackward)) {
        std::cout << "Moving backward" << std::endl;
        m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForward() * m_Camera.GetSpeed());
    }
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveLeft)) {
        m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRight() * m_Camera.GetSpeed());
    }
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveRight)) {
        m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRight() * m_Camera.GetSpeed());
    }
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveUp)) {
        m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetUp() * m_Camera.GetSpeed());
    }
    if (m_Input.IsActionHeld(InputManager::m_ActionType::MoveDown)) {
        m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetUp() * m_Camera.GetSpeed());
    }
}

void FirstPersonController::CameraMouseMovement(float deltaTime)
{
    // Get mouse movement
    double xpos, ypos;
    m_Camera .SetSpeed((deltaTime * 2.5f));
	m_Input.GetMousePosition(xpos, ypos);
    
    static double lastX = xpos;
    static double lastY = ypos;
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    // Sensitivity can be adjusted
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update camera yaw and pitch
    m_Camera.SetYaw(m_Camera.GetYaw() + xoffset);
    m_Camera.SetPitch(m_Camera.GetPitch() + yoffset);

    // Clamp the pitch value to prevent flipping
    if (m_Camera.GetPitch() > 89.0f)
        m_Camera.SetPitch(89.0f);
    if (m_Camera.GetPitch() < -89.0f)
        m_Camera.SetPitch(-89.0f);

    // Update camera direction based on yaw and pitch
	m_Camera.CalculateDirection();
}



