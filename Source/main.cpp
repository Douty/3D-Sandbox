using namespace std;

#include <iostream>
#include <glad/glad.h>

#include <Core/Window.hpp>
#include "Core/InputManager.hpp"
#include "Core/Camera.hpp"
#include "Render/EBO.hpp"
#include "Render/VBO.hpp"
#include "Render/VAO.hpp"
#include "Render/Shader.hpp"
#include <Core/FirstPersonController.hpp>
#include "Render/ModelLoading/Model.hpp"

void APIENTRY DebugCallback(GLenum src, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* user) {
	std::fprintf(stderr, "[GL DEBUG] %u: %s\n", id, message);
}


int main() {
	std::string windowTitle = "3D Sandbox";
	int windowWidth = 1920;
	int windowHeight = 1080;
	

	Engine::Core::Window window(windowTitle, windowWidth, windowHeight);

	Engine::Core::InputManager inputManager(window.GetGLFWwindow());

	namespace Core = Engine::Core;
	namespace Render = Engine::Render;



	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // get messages immediately (easier to debug)
	glDebugMessageCallback(DebugCallback, nullptr);

	
	Render::VAO vao;
	

	Render::Model Triangle ("Assets/Models/Triangle/triangle.obj");
	Render::Model Sphere("Assets/Models/Sphere/sphere.obj");

	Render::Shader shader("Assets/Shaders/cube.vert", "Assets/Shaders/cube.frag");
	Render::Shader shader2("Assets/Shaders/shader2.vert", "Assets/Shaders/shader2.frag");

	Core::Camera camera;
	camera.UpdateProjectionMatrix(45.0f,static_cast<float>(window.GetWidth()),static_cast<float>(window.GetHeight()),0.1f, 100.0f);
	Core::FirstPersonController controller(camera, inputManager);
	
	glEnable(GL_DEPTH_TEST);
	double last = glfwGetTime();

	while (!window.ShouldClose()) {

		double now = glfwGetTime();
		float dt = static_cast<float>(now - last);
		last = now;

		window.PollEvents();
		camera.UpdateViewMatrix();
		inputManager.Update();
		controller.Update(dt);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		vao.Bind();
		shader.Use();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -2.0f }); // move quad toward -Z
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();  // near ~0.1f, far ~100.0f

		
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		shader2.SetMat4("model", model);
		shader2.SetMat4("view", view);
		shader2.SetMat4("projection", projection);
		
		Triangle.Draw(shader2);
		Sphere.Draw(shader);
		

	

		window.SwapBuffers();
	}
	return 0;
}