#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h> 
namespace Engine::Render {


	class Shader {

	public:
		Shader(std::string vertexShader, std::string fragementShader);
		~Shader();

		void Use() const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec2(const std::string& name, glm::vec2) const;
		void SetVec3(const std::string& name, glm::vec3) const;
		void SetVec4(const std::string& name, glm::vec4 value) const;
		void SetMat3(const std::string& name, glm::mat3 value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;


	private:
		unsigned int CompileShader(const std::string& shaderCode, GLenum shaderType) const;
		std::string ReadShaderFile(const std::string& filePath) const;
		GLuint LocateUniform(const std::string& name) const;
		void CheckCompileErrors(unsigned int shader, const std::string& type) const;
		

	private:
		unsigned int m_ID = 0;
		std::string m_VertexShader;
		std::string m_FragmentShader;


	};

}