#pragma once

#include "GL\glew.h"
#include "glm\glm.hpp"
#include <string>

class Texture
{
public:
	Texture(std::string filename);
	~Texture();

	void bind() const;

	GLuint getTextureID() const;
	glm::ivec2 getDimensions() const;

private:
	Texture(const Texture&);
	Texture& operator=(const Texture&);

	GLuint m_textureID;
	glm::ivec2 m_dimensions;
};