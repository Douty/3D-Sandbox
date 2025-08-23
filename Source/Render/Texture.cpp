#include "Render/Texture.hpp"
#include <stb_image.h>
#include <iostream>
using namespace Engine::Render;

Texture::Texture(const char* filePath) {
	Generate2DTexture(filePath);
}
Texture::~Texture() {
	if (m_ID != 0) {
		glDeleteTextures(1, &m_ID);
	}
}
void Texture::Generate2DTexture(const char* filePath) {
	stbi_set_flip_vertically_on_load(true);
	int width = 0, height = 0, channels = 0;
	unsigned char* data = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
	if (!data) {
		std::cerr << "Failed to load texture: " << filePath << std::endl;
		return;
	}
	channels = 4;
	glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);


	const int levels = CalcMipmapLevels(width, height);
	const GLenum internalFormat = GL_SRGB8_ALPHA8;


	glTextureStorage2D(m_ID, levels, internalFormat, width, height);

	GLint prevUnpackAlign = 0;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevUnpackAlign);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glTextureSubImage2D(m_ID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glPixelStorei(GL_UNPACK_ALIGNMENT, prevUnpackAlign);

	glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateTextureMipmap(m_ID);

	if (glGetError() != GL_NO_ERROR) {
		std::cerr << "Error generating texture: " << filePath << std::endl;
	}



	stbi_image_free(data);
}

void Texture::Bind(GLuint slot) const
{
	glBindTextureUnit(slot, m_ID);
}

 inline int Texture::CalcMipmapLevels(int w, int h) {
	int m = (w > h ? w : h);
	int levels = 1;
	while (m > 1) { m >>= 1; ++levels; }
	return levels;
}
