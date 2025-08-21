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

	
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // get messages immediately (easier to debug)
	glDebugMessageCallback(DebugCallback, nullptr);

	float vertices[] = {
		// Front (z = +0.5)  – red
		-0.5f,-0.5f, 0.5f,   1,0,0,
		 0.5f,-0.5f, 0.5f,   1,0,0,
		 0.5f, 0.5f, 0.5f,   1,0,0,
		-0.5f, 0.5f, 0.5f,   1,0,0,

		// Back (z = -0.5) – green
		 0.5f,-0.5f,-0.5f,   0,1,0,
		-0.5f,-0.5f,-0.5f,   0,1,0,
		-0.5f, 0.5f,-0.5f,   0,1,0,
		 0.5f, 0.5f,-0.5f,   0,1,0,

		 // Left (x = -0.5) – blue
		 -0.5f,-0.5f,-0.5f,   0,0,1,
		 -0.5f,-0.5f, 0.5f,   0,0,1,
		 -0.5f, 0.5f, 0.5f,   0,0,1,
		 -0.5f, 0.5f,-0.5f,   0,0,1,

		 // Right (x = +0.5) – yellow
		  0.5f,-0.5f, 0.5f,   1,1,0,
		  0.5f,-0.5f,-0.5f,   1,1,0,
		  0.5f, 0.5f,-0.5f,   1,1,0,
		  0.5f, 0.5f, 0.5f,   1,1,0,

		  // Top (y = +0.5) – magenta
		  -0.5f, 0.5f, 0.5f,   1,0,1,
		   0.5f, 0.5f, 0.5f,   1,0,1,
		   0.5f, 0.5f,-0.5f,   1,0,1,
		  -0.5f, 0.5f,-0.5f,   1,0,1,

		  // Bottom (y = -0.5) – cyan
		  -0.5f,-0.5f,-0.5f,   0,1,1,
		   0.5f,-0.5f,-0.5f,   0,1,1,
		   0.5f,-0.5f, 0.5f,   0,1,1,
		  -0.5f,-0.5f, 0.5f,   0,1,1,
	};

	unsigned int indices[] = {
		// 6 faces * 2 tris * 3 = 36 indices
		0,1,2,  2,3,0,      // front
		4,5,6,  6,7,4,      // back
		8,9,10, 10,11,8,    // left
		12,13,14, 14,15,12, // right
		16,17,18, 18,19,16, // top
		20,21,22, 22,23,20  // bottom
	};

	Engine::Render::VAO vao;
	Engine::Render::VBO vbo(vertices, sizeof(vertices));
	Engine::Render::EBO ebo(indices, sizeof(indices),GL_STATIC_DRAW);
	vao.LinkEBO(ebo.GetID());
	vao.LinkAttrib(/*attribIndex*/0, /*bindingIndex*/0, vbo.GetID(),
		/*size*/3, GL_FLOAT, GL_FALSE,
		/*relativeOffset*/0,
		/*stride*/6 * sizeof(float),
		/*bindingOffset*/0);
	 
	vao.LinkAttrib(/*attribIndex*/1, /*bindingIndex*/0, vbo.GetID(),
		/*size*/3, GL_FLOAT, GL_FALSE,
		/*relativeOffset*/3 * sizeof(float),
		/*stride*/6 * sizeof(float),
		/*bindingOffset*/0);
	
	Engine::Render::Shader shader("Assets/Shaders/cube.vert", "Assets/Shaders/cube.frag");

	Engine::Core::Camera camera;
	camera.UpdateProjectionMatrix(45.0f,static_cast<float>(window.GetWidth()),static_cast<float>(window.GetHeight()),0.1f, 100.0f);
	Engine::Core::FirstPersonController controller(camera, inputManager);
	
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
			

		

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		window.SwapBuffers();
	}
	return 0;
}