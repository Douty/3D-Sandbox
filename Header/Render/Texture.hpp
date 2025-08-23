#pragma once
#include "glad/glad.h"
namespace Engine::Render {
	class Texture {
	public:
		Texture(const char* filePath);
		~Texture();

		Texture(const Texture&) = delete; 
		Texture& operator=(const Texture&) = delete; 
		Texture(Texture&& other) noexcept : m_ID(other.m_ID) {
			other.m_ID = 0; 
		}

		Texture& operator=(Texture&& other) noexcept {
			if (this != &other) {
				glDeleteTextures(1, &m_ID); 
				m_ID = other.m_ID; 
				other.m_ID = 0; 
			}
			return *this;
		}
		void Generate2DTexture(const char* filePath);
		GLuint GetID() const { return m_ID; }
		void Bind(GLuint slot = 0) const;
		static int CalcMipmapLevels(int w, int h);
	private:
		GLuint m_ID = 0;

	};
} 