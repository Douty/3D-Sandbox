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
	namespace Core = Engine::Core;
	namespace Render = Engine::Render;

	std::string windowTitle = "3D Sandbox";
	int windowWidth = 1920;
	int windowHeight = 1080;
	

	Core::Window window(windowTitle, windowWidth, windowHeight);

	Core::InputManager inputManager(window.GetGLFWwindow());

	


	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // get messages immediately (easier to debug)
	glDebugMessageCallback(DebugCallback, nullptr);

	
	Render::VAO vao;
	

	
	Render::Model platform("Assets/Models/Platform/platform.obj");
	Render::Model backpack("Assets/Models/Backpack/backpack.obj");
	Render::Model lightsphere("Assets/Models/Sphere/sphere.obj");

	Render::Shader shader("Assets/Shaders/cube.vert", "Assets/Shaders/cube.frag");
	Render::Shader lightshader("Assets/Shaders/LightSource.vert", "Assets/Shaders/LightSource.frag");
	

	Core::Camera camera;
	camera.UpdateProjectionMatrix(45.0f,static_cast<float>(window.GetWidth()),static_cast<float>(window.GetHeight()),0.1f, 100.0f);
	Core::FirstPersonController controller(camera, inputManager);
	
	glEnable(GL_DEPTH_TEST);
	double last = glfwGetTime();

	glm::vec3 coral(1.0f, 0.5f, 0.31f);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	

	
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



		glm::mat4 model = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -2.0f }); // move quad toward -Z
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();  // near ~0.1f, far ~100.0f
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(view * model)));

		glm::vec3 lightPos;
		lightPos.x = 1.2f * sin(static_cast<float>(now));
		lightPos.y = 1.0f;
		lightPos.z = 2.0f * cos(static_cast<float>(now));

		glm::vec3 lightPosWorld = lightPos;
		glm::vec4 lightView = camera.GetViewMatrix() * glm::vec4(lightPosWorld, 1.0f);


		shader.Use();
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		shader.SetMat3("normalMatrix", normalMatrix);
	

		shader.SetVec3("light.ambient", { 0.2f, 0.2f, 0.2f });
		shader.SetVec3("light.diffuse", {0.5f, 0.5f, 0.5f}); 
		shader.SetVec3("light.specular", { 1.0f, 1.0f, 1.0f });
		shader.SetFloat("material.shininess", 32.0f);
		shader.SetVec3("lightPos", glm::vec3(lightView));
		
		
		backpack.Draw(shader);
		


		glm::mat4 modelLight = glm::mat4(1.0f);
		modelLight = glm::translate(modelLight, lightPos);
		modelLight = glm::scale(modelLight, glm::vec3(0.5f));

		lightshader.Use();
		lightshader.SetMat4("model", modelLight);
		lightshader.SetMat4("view", view);
		lightshader.SetMat4("projection", projection);
		

		lightsphere.Draw(lightshader);

	

		window.SwapBuffers();
	}
	return 0;
}