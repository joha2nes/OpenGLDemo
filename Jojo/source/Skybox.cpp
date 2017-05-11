#include "Skybox.hpp"
#include "Camera.hpp"
#include "glm\gtx\transform.hpp"

Skybox::Skybox(std::string filename)
{
	m_texture = new Texture(filename);

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
	};

	Vertex vertices[] =
	{
		// 0
		glm::vec3(-1.0f, +1.0f, +1.0f),
		glm::vec2(0.25f, 0.00f),
		// 1
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec2(0.50f, 0.00f),
		// 2
		glm::vec3(-1.0f, +1.0f, +1.0f),
		glm::vec2(0.00f, 0.335f),
		// 3
		glm::vec3(-1.0f, +1.0f, -1.0f),
		glm::vec2(0.25f, 0.335f),
		// 4
		glm::vec3(+1.0f, +1.0f, -1.0f),
		glm::vec2(0.50f, 0.335f),
		// 5
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec2(0.75f, 0.335f),
		// 6
		glm::vec3(-1.0f, +1.0f, +1.0f),
		glm::vec2(1.00f, 0.335f),
		// 7
		glm::vec3(-1.0f, -1.0f, +1.0f),
		glm::vec2(0.00f, 0.666f),
		// 8
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec2(0.25f, 0.666f),
		// 9
		glm::vec3(+1.0f, -1.0f, -1.0f),
		glm::vec2(0.50f, 0.666f),
		// 10
		glm::vec3(+1.0f, -1.0f, +1.0f),
		glm::vec2(0.75f, 0.666f),
		// 11
		glm::vec3(-1.0f, -1.0f, +1.0f),
		glm::vec2(1.00f, 0.666f),
		// 12
		glm::vec3(-1.0f, -1.0f, +1.0f),
		glm::vec2(0.25f, 1.00f),
		// 13
		glm::vec3(+1.0f, -1.0f, +1.0f),
		glm::vec2(0.50f, 1.00f),
	};

	GLushort indices[] =
	{
		4, 9, 10, 10, 5, 4,  // +x
		2, 7, 8, 8, 3, 2,    // -x
		0, 3, 4, 4, 1, 0,    // +y
		8, 12, 13, 13, 9, 8, // -y
		5, 10, 11, 11, 6, 5, // +z
		3, 8, 9, 9, 4, 3,    // -z
	};

	// create vertex buffer object
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	// create vertex array object
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// create index buffer object
	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}
Skybox::~Skybox()
{
	delete m_texture;
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteBuffers(1, &m_indexBufferID);
}

void Skybox::draw()
{
	m_texture->bind();
	
	glBindVertexArray(m_vertexArrayID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}
