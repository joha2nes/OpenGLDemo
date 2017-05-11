#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename)
{
	// load image data
	int width, height, numComponents;
	stbi_uc* imageData = stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	// check if image is loaded
	if (imageData == nullptr)
		assert(false && "couldnt find or open texture file");
	else {
		m_dimensions = glm::ivec2(width, height);

		// create texture object in gpu
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		// unload image data
		stbi_image_free(imageData);
	}
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint Texture::getTextureID() const
{
	return m_textureID;
}
glm::ivec2 Texture::getDimensions() const
{
	return m_dimensions;
}