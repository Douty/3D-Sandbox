#pragma once
#include "Render/VBO.hpp"

namespace Engine::Render {
	class VAO {
	public:
		VAO();
		~VAO();
		
		VAO(const VAO&) = delete;
		VAO& operator=(const VAO&) = delete;

		VAO(VAO&& other) noexcept : m_ID(other.m_ID) {
			other.m_ID = 0;
		}
		VAO& operator=(VAO&& other) noexcept {
			if (this != &other) {
				Delete();
				m_ID = other.m_ID;
				other.m_ID = 0;
			}
			return *this;
		}

		void Bind() const;
		void Unbind() const;
		void LinkEBO(GLuint eboID) const;
		void LinkAttrib(GLuint attribIndex, GLuint bindingIndex, GLuint vboID, GLint size,
			GLenum type, GLboolean isNormalized, GLuint realativeOffset, GLsizei stride, GLuint bindingOffset) const;
		void Delete() const;
		
	private:
		GLuint m_ID = 0;

	};
}