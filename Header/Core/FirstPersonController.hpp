#include "InputManager.hpp"
#include "Camera.hpp"

namespace Engine::Core
{
	class FirstPersonController
	{
	public:
		FirstPersonController(Camera& camera, InputManager& input);
		void Update(float deltaTime);
		
		Camera& GetCamera() { return m_Camera; }
		InputManager& GetInputManager() { return m_Input; }

		void SetCamera(Camera& camera) { m_Camera = camera; }
		void SetInputManager(InputManager& input) { m_Input = input; }

		void CameraMovement(float deltaTime);
		void CameraMouseMovement(float deltaTime);
		void CameraZoom(GLFWwindow* window, double xoffset, double yoffset);
		

	private:
		Camera& m_Camera;
		InputManager& m_Input;
		
	};
}