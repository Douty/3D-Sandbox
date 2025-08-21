
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../Header/Core/Window.hpp"
#include <stdexcept>

using namespace Engine::Core;

Engine::Core::Window::Window(const std::string& title, int width, int height)
	: m_title(title), m_width(width), m_height(height) {
	
	m_Init();
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		throw std::runtime_error("Failed to initialize GLAD");
	}

	int fbw, fbh;
	glfwGetFramebufferSize(m_window, &fbw, &fbh);
	glViewport(0, 0, fbw, fbh);

	glfwSetWindowUserPointer(m_window, this);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(m_window, s_resizeCallback);
}

Engine::Core::Window::~Window()
{
	if (m_window) {
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}

	glfwTerminate();
}

void Engine::Core::Window::SetPosition(int x, int y)
{
	if (m_window) {
		glfwSetWindowPos(m_window, x, y);
	}
}

int Engine::Core::Window::GetWidth() const{ return m_width; }
int Engine::Core::Window::GetHeight() const { return m_height; }

void Engine::Core::Window::m_Init() {

	if (!glfwInit()) 
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Engine::Core::Window::s_resizeCallback(GLFWwindow* window, int width, int height) 
{

	glViewport(0, 0, width, height);
}

void Engine::Core::Window::PollEvents()
{
	glfwPollEvents();
}

bool Engine::Core::Window::ShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Engine::Core::Window::SwapBuffers() {
	if (m_window) {
		glfwSwapBuffers(m_window);
	}
}

GLFWwindow* Engine::Core::Window::GetGLFWwindow() const{ { return m_window; } }
