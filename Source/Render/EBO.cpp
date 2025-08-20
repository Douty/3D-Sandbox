#include "Render/EBO.hpp"

#include <glad/glad.h>

using namespace Engine::Render;

Engine::Render::EBO::EBO()
{
	glCreateBuffers(1, &m_ID);
}

Engine::Render::EBO::EBO(const void* indices, GLsizeiptr size, GLenum usage=GL_STATIC_DRAW) : EBO()
{
	glNamedBufferData(m_ID, size, indices, usage);
}

Engine::Render::EBO::~EBO()
{
	if (m_ID != 0)
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}
}
 void Engine::Render::EBO::Delete()
{
	if (m_ID != 0)
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}
}

void Engine::Render::EBO::SetData(const void* indices, GLsizeiptr size, GLenum usage) const
{
	glNamedBufferData(m_ID, size, indices, usage);
}
void Engine::Render::EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
void Engine::Render::EBO::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
