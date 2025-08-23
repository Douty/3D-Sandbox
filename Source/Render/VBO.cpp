#include "Render/VBO.hpp"



using namespace Engine::Render;


Engine::Render::VBO::VBO() 
{
	glCreateBuffers(1, &m_ID);
}

Engine::Render::VBO::VBO(const void* vertices, GLsizeiptr size) : VBO()
{
	glNamedBufferData(m_ID, size, vertices, GL_STATIC_DRAW);
}

Engine::Render::VBO::~VBO()
{
	if (m_ID != 0) {
		glDeleteBuffers(1, &m_ID);
	}
}


void Engine::Render::VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}
void Engine::Render::VBO::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::Render::VBO::Delete() const
{
	glDeleteBuffers(1, &m_ID);
}