#include "Render/VAO.hpp"

#include <glad/glad.h>
#include "Render/EBO.hpp"

using namespace Engine::Render;

Engine::Render::VAO::VAO() 
{
	glCreateVertexArrays(1, &m_ID);
}
Engine::Render::VAO::~VAO()
{
	if (m_ID != 0) {
		glDeleteVertexArrays(1, &m_ID);
	}
}
void Engine::Render::VAO::LinkEBO(GLuint eboID) const
{
	glVertexArrayElementBuffer(m_ID, eboID);
}
void Engine::Render::VAO::LinkAttrib(GLuint attribIndex, GLuint bindingIndex ,GLuint vboID, GLint size,
	GLenum type, GLboolean isNormalized, GLuint realativeOffset,GLsizei stride, GLuint bindingOffset) const
{
	glVertexArrayVertexBuffer(m_ID, bindingIndex, vboID, bindingOffset, stride);
	glEnableVertexArrayAttrib(m_ID, attribIndex);
	
	glVertexArrayAttribFormat(m_ID, attribIndex, size, type, isNormalized, realativeOffset);
	glVertexArrayAttribBinding(m_ID, attribIndex, bindingIndex);
	
}
void Engine::Render::VAO::Bind() const
{
	glBindVertexArray(m_ID);
}