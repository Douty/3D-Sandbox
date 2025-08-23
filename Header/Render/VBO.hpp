#pragma once
#include <glad/glad.h>


namespace Engine::Render
{
	class VBO {
	public:
		VBO();
		VBO(const void* vertices, GLsizeiptr size);
		~VBO();
		VBO(const VBO&) = delete;
		VBO& operator=(const VBO&) = delete;
		VBO(VBO&& other) noexcept: m_ID(other.m_ID)
		{
			other.m_ID = 0;
		}
		VBO& operator=(VBO&& other) noexcept
		{
			if (this != &other)
			{
				Delete();
				m_ID = other.m_ID;
				other.m_ID = 0;
			}
			return *this;
		}
	
		void Bind() const;
		void Unbind() const;
		void Delete() const;
		unsigned int GetID() const { return m_ID; }

	private:
		GLuint m_ID;

		

	};
}