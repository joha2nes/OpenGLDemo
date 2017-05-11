#include "Sprite.hpp"
#include "Texture.hpp"
#include "glm\gtx\transform.hpp"

Sprite::Sprite(Texture* t)
	: Sprite(t, 0, 0, t->getDimensions().x, t->getDimensions().y)
{}
Sprite::Sprite(Texture* t, GLuint x, GLuint y, GLuint w, GLuint h)
{
	m_texture = t;

	// create and load vertex buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	float _x = (float)x / (float)t->getDimensions().x;
	float _y = (float)y / (float)t->getDimensions().y;
	float _w = (float)w / (float)t->getDimensions().x;
	float _h = (float)h / (float)t->getDimensions().y;

	struct Vertex
	{
		glm::vec2 position;
		glm::vec2 texCoord;
	};

	Vertex vertices[] =
	{
		{ { 0.0f, 0.0f }, { _x, _y } },
		{ { 0.0f, 1.0f }, { _x, _y + _h } },
		{ { 1.0f, 1.0f }, { _x + _w, _y + _h } },
		{ { 1.0f, 1.0f }, { _x + _w, _y + _h } },
		{ { 1.0f, 0.0f }, { _x + _w, _y } },
		{ { 0.0f, 0.0f }, { _x, _y } },
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	// create and load vertex array object
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// cleanup
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Sprite::~Sprite()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void Sprite::draw() const
{
	m_texture->bind();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Texture* Sprite::getTexture() const
{
	return m_texture;
}
GLuint Sprite::getVBO() const
{
	return m_VBO;
}
GLuint Sprite::getVAO() const
{
	return m_VAO;
}
