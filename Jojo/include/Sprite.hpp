#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"

class Texture;
class Sprite
{
public:
	Sprite(Texture*);
	Sprite(Texture*, GLuint x, GLuint y, GLuint w, GLuint h);
	~Sprite();

	void draw() const;

	Texture* getTexture() const;
	GLuint getVBO() const;
	GLuint getVAO() const;

private:
	Texture* m_texture;
	GLuint m_VBO;
	GLuint m_VAO;
};

/*
class Shader;
class Texture;
class Sprite
{
public:
	Sprite(Shader*, Texture*);
	Sprite(Shader*, Texture*, Rect);
	~Sprite();

	void draw(glm::vec2 position);
	void draw(glm::vec2 position, glm::vec2 scale);
	void draw(glm::vec2 position, glm::vec2 scale, float rotation);
	void draw(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color);

private:
	Sprite(const Sprite&);
	Sprite& operator=(const Sprite&);

	GLuint m_vertexBufferID;
	GLuint m_vertexArrayID;
	Shader* m_shader;
	Texture* m_texture;
	Rect m_texCoords;
};
*/