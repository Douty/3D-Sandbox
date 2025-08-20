using namespace std;

#include <iostream>
#include <glad/glad.h>

#include <Core/Window.hpp>
#include "Core/InputManager.hpp"
#include "Render/EBO.hpp"
#include "Render/VBO.hpp"
#include "Render/VAO.hpp"
#include "Render/Shader.hpp"


int main() {
	std::string windowTitle = "3D Sandbox";
	int windowWidth = 1920;
	int windowHeight = 1080;
	
	Engine::Core::Window window(windowTitle, windowWidth, windowHeight);

	Engine::Core::InputManager inputManager(window.GetGLFWwindow());

	

	float vertices[] = {
		// position        // color
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // red
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // green
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // blue
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f  // white
	};

	unsigned int indices[] = {
	0, 1, 3, 
	1, 2, 3  
	};

	Engine::Render::VAO vao;
	Engine::Render::VBO vbo(vertices, sizeof(vertices));
	Engine::Render::EBO ebo(indices, sizeof(indices),GL_STATIC_DRAW);
	vao.LinkEBO(ebo.GetID());
	vao.LinkAttrib(0, 0, vbo.GetID(), 3, GL_FLOAT, GL_FALSE,0, 3 * sizeof(float), 0);
	vao.LinkAttrib(1, 0, vbo.GetID(), 3, GL_FLOAT, GL_FALSE, 0, 6 * sizeof(float), 0);
	Engine::Render::Shader shader("Assets/Shaders/cube.vert", "Assets/Shaders/cube.frag");
	
	

	while (!window.ShouldClose()) {
		window.PollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		shader.Use();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		window.SwapBuffers();
	}
	return 0;
}