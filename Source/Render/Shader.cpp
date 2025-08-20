#include "Render/Shader.hpp"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
using namespace Engine::Render;


Engine::Render::Shader::Shader(std::string vertexShader, std::string fragementShader):m_ID(0)
{
	unsigned int vertex, fragment;

	vertex = CompileShader(ReadShaderFile(vertexShader), GL_VERTEX_SHADER);
	fragment = CompileShader(ReadShaderFile(fragementShader), GL_FRAGMENT_SHADER);
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	CheckCompileErrors(m_ID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}



Engine::Render::Shader::~Shader()
{
	if (m_ID != 0)
	{
		glDeleteProgram(m_ID);
		m_ID = 0;
	}
}

void Engine::Render::Shader::Use() const
{
	glUseProgram(m_ID);
}

unsigned int Engine::Render::Shader::CompileShader(const std::string& shaderCode, GLenum shaderType) const
{
	const char* source = shaderCode.c_str();
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	CheckCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
	return shader;
}




void Engine::Render::Shader::SetBool(const std::string& name, bool value) const
{
	glProgramUniform1i(m_ID,LocateUniform(name), (int)value);
}
void Engine::Render::Shader::SetInt(const std::string& name, int value) const
{
	glProgramUniform1i(m_ID, LocateUniform(name), value);
}
void Engine::Render::Shader::SetFloat(const std::string& name, float value) const
{
	glProgramUniform1f(m_ID, LocateUniform(name), value);
}
void Engine::Render::Shader::SetVec2(const std::string& name, glm::vec2 value) const
{
	glProgramUniform2fv(m_ID, LocateUniform(name), 1, glm::value_ptr(value));
}
void Engine::Render::Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
	glProgramUniform3fv(m_ID, LocateUniform(name), 1, glm::value_ptr(value));
}
void Engine::Render::Shader::SetVec4(const std::string& name, glm::vec4 value) const
{
	glProgramUniform4fv(m_ID, LocateUniform(name), 1, glm::value_ptr(value));
}
void Engine::Render::Shader::SetMat3(const std::string& name, glm::mat3 value) const
{
	glProgramUniformMatrix3fv(m_ID, LocateUniform(name), 1, GL_FALSE, glm::value_ptr(value));
}
void Engine::Render::Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glProgramUniformMatrix4fv(m_ID, LocateUniform(name), 1, GL_FALSE, glm::value_ptr(value));
}





std::string Engine::Render::Shader::ReadShaderFile(const std::string& filePath) const
{
	std::string shaderCode;
	std::ifstream shaderFile(filePath);
	if (!shaderFile.is_open())
	{
		std::cerr << "Error: Could not open shader file: " << filePath << std::endl;
		return "";
	}
	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();
	shaderCode = shaderStream.str();
	if (shaderCode.empty())
	{
		std::cerr << "Error: Shader file is empty: " << filePath << std::endl;
		return "";
	}

	return shaderCode;
};

GLuint Engine::Render::Shader::LocateUniform(const std::string& name) const
{
	GLuint location = glGetUniformLocation(m_ID, name.c_str());
	if (location == -1)
	{
		std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
	}
	return location;
}

void Engine::Render::Shader::CheckCompileErrors(unsigned int shader, const std::string& type) const
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "Error: Shader compilation error of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "Error: Program linking error of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}


