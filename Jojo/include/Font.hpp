#pragma once
#include <string>
#include <map>
#include "Texture.hpp"
#include "glm\glm.hpp"

struct Glyph
{
	GLuint textureObj;
	GLuint vertexBufferObj;
	GLuint vertexArrayObj;
	GLuint advance;

	Glyph(GLuint textureObj, GLuint vertexBufferObj, GLuint vertexArrayObj, GLuint advance);
};

class Font
{
public:
	Font(std::string filename);
	~Font();
	
	Glyph getGlyph(GLchar character);

private:
	std::map<GLchar, Glyph> m_glyphs;
};