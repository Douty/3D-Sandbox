#pragma once


#include <unordered_map>
#include <GLFW/glfw3.h>
struct GLFWwindow;
namespace Engine::Core {

	class InputManager {

	public:

		struct m_Action
		{
			int m_key;
			bool m_isPressed;
			bool m_isReleased;
			bool m_isKeyHeld;
		};
		enum class m_ActionType {
			MoveForward,
			MoveBackward,
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Count
		};

		InputManager(GLFWwindow* window);
			

		void Update();

		GLFWwindow* GetWindow() const { return m_window; }
			
			
			
		bool IsActionPressed( m_ActionType action) const;
		bool IsActionReleased( m_ActionType action) const;
		bool IsActionHeld(m_ActionType action) const;

		
			
		void GetMousePosition(double& x, double& y) const;
		void SetMousePosition(double x, double y);
		void SetWindow(void* window);

			
		// Map action types to their corresponding keys and states
			 
			
		std::unordered_map<m_ActionType, m_Action> keyBinds = {
			{m_ActionType::MoveForward, {GLFW_KEY_W, false, false}},
			{m_ActionType::MoveBackward, {GLFW_KEY_S, false, false}},
			{m_ActionType::MoveLeft, {GLFW_KEY_A, false, false}},
			{m_ActionType::MoveRight, {GLFW_KEY_D, false, false}},
			{m_ActionType::MoveUp, {GLFW_KEY_SPACE, false, false}},
			{m_ActionType::MoveDown, {GLFW_KEY_LEFT_SHIFT, false, false}}
		};

	private:
		bool IsKeyPressed(int key) const;

		bool IsKeyReleased(int key) const;

		bool IsKeyHeld(int key) const;
		
		bool IsMouseButtonPressed(int button) const;
		bool IsMouseButtonReleased(int button) const;
		bool IsMouseButtonHeld(int button) const;

	private:
		float m_xOffset = 0.0f;
		float m_yOffset = 0.0f;
		double m_mouseX = 0.0;
		double m_mouseY = 0.0;
		double m_lastMouseX = 0.0;
		double m_lastMouseY = 0.0;
		GLFWwindow* m_window = nullptr;
		


	};


};

