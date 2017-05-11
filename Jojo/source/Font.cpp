#include "Font.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H
#include <cassert>

Glyph::Glyph(GLuint to, GLuint vbo, GLuint vao, GLuint a)
	: textureObj(to)
	, vertexBufferObj(vbo)
	, vertexArrayObj(vao)
	, advance(a)
{}

Font::Font(std::string filename)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		assert(false && "couldnt initialize FreeType library");
	else
	{
		FT_Face face;
		if (FT_New_Face(ft, filename.c_str(), 0, &face))
		{
			FT_Done_FreeType(ft);
			assert(false && "couldnt find, open or load Font file");
		}
		else
		{
			FT_Set_Pixel_Sizes(face, 0, 48);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			for (int i = 0; i < 128; i++)
			{
				char character = (char)i;
				if (FT_Load_Char(face, character, FT_LOAD_RENDER))
					continue;
				else
				{
					// get some important glyph values
					glm::vec2 size = glm::vec2((float)face->glyph->bitmap.width, (float)face->glyph->bitmap.rows);
					glm::vec2 bearing = glm::vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top);
					GLuint advance = face->glyph->advance.x / 64;

					// create texture object
					GLuint textureObj;
					glGenTextures(1, &textureObj);
					glBindTexture(GL_TEXTURE_2D, textureObj);
					glTexImage2D(
						GL_TEXTURE_2D,
						0,
						GL_RED,
						face->glyph->bitmap.width,
						face->glyph->bitmap.rows,
						0,
						GL_RED,
						GL_UNSIGNED_BYTE,
						face->glyph->bitmap.buffer
						);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					// create vertex buffer object
					struct Vertex
					{
						glm::vec2 position;
						glm::vec2 texCoord;
					};

					glm::vec2 min = glm::vec2(bearing.x, bearing.y - size.y);
					glm::vec2 max = glm::vec2(bearing.x + size.x, bearing.y);

					Vertex vertices[] =
					{
						// t1
						glm::vec2(min.x, 36.0f),
						glm::vec2(0.0f, 1.0f),
						glm::vec2(max.x, 36.0f),
						glm::vec2(1.0f, 1.0f),
						glm::vec2(max.x, 0),
						glm::vec2(1.0f, 0.0f),
						// t2
						glm::vec2(max.x, 0.0f),
						glm::vec2(1.0f, 0.0f),
						glm::vec2(min.x, 0.0f),
						glm::vec2(0.0f, 0.0f),
						glm::vec2(min.x, 36.0f),
						glm::vec2(0.0f, 1.0f),
					};
					GLuint vertexBufferObj;
					glGenBuffers(1, &vertexBufferObj);
					glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
					glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

					// create vertex array object
					GLuint vertexArrayObj;
					glGenVertexArrays(1, &vertexArrayObj);
					glBindVertexArray(vertexArrayObj);
					glEnableVertexAttribArray(0);
					glEnableVertexAttribArray(1);
					glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
					glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec2));

					// clean some little up
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindVertexArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);

					// save the glyph
					m_glyphs.insert(std::pair<GLchar, Glyph>(character, Glyph(textureObj, vertexBufferObj, vertexArrayObj, advance)));
				}
			}

			// cleanup when done
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}
	}
}
Font::~Font()
{
	for (std::pair<GLchar, Glyph> p : m_glyphs)
	{
		glDeleteTextures(1, &p.second.textureObj);
		glDeleteVertexArrays(1, &p.second.vertexArrayObj);
		glDeleteBuffers(1, &p.second.vertexBufferObj);
	}
}

Glyph Font::getGlyph(GLchar character)
{
	return m_glyphs.at(character);
}