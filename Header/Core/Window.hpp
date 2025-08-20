#pragma once


#include <string>
struct GLFWwindow;

namespace Engine::Core {
	class Window {

	public:
		Window(const std::string& title, int width, int height);
		~Window();
		void SetPosition(int x, int y);
		int GetWidth() const;
		int GetHeight() const;
		void PollEvents();
		bool ShouldClose() const;
		void SwapBuffers();
		GLFWwindow* GetGLFWwindow() const;
	private:
		void m_Init();


	private:
		GLFWwindow* m_window;
		std::string m_title;
		static void s_resizeCallback(GLFWwindow* window,int width, int height);
		int m_width;
		int m_height;

	};

};