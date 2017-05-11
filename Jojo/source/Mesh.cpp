#include "Mesh.hpp"

Vertex::Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) : position(p), normal(n), texCoord(t)
{}

MeshData::MeshData(const std::vector<Vertex>& v, const std::vector<GLuint>& i)
	: vertices(v), indices(i)
{}

Mesh::Mesh(MeshData m)
	: Mesh(m.vertices, m.indices, false)
{}
Mesh::Mesh(std::vector<Vertex> vertices)
	: Mesh(vertices, std::vector<GLuint>(0), false)
{}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, bool autoNormals)
{
	m_numVertices = vertices.size();
	m_numIndices = indices.size();

	// generate normals?
	if (autoNormals && m_numIndices > 0)
		generateNormals(&vertices, indices);

	// create vertex buffer object
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_numVertices, &vertices[0], GL_STATIC_DRAW);

	// create vertex array object
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec3)));

	// create index buffer object
	if (m_numIndices > 0)
	{
		glGenBuffers(1, &m_indexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_numIndices, &indices[0], GL_STATIC_DRAW);
	}
	else
		m_indexBufferID = 0;

	// get mesh radius
	float maxRadius = 0.0f;
	for (auto v : vertices) {
		float distance = glm::length(v.position);
		if (distance > maxRadius)
			maxRadius = distance;
	}
	m_radius = maxRadius;
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteBuffers(1, &m_indexBufferID);
}

void Mesh::bind() const
{
	glBindVertexArray(m_vertexArrayID);
}
void Mesh::draw() const
{
	if (m_numIndices > 0)
		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
}

GLuint Mesh::getVertexBufferID() const { return m_vertexBufferID; }
GLuint Mesh::getVertexArrayID() const { return m_vertexArrayID; }
GLuint Mesh::getIndexBufferID() const { return m_indexBufferID; }
GLuint Mesh::getNumVertices() const { return m_numVertices; }
GLuint Mesh::getNumIndices() const { return m_numIndices; }
GLfloat Mesh::getRadius() const { return m_radius; }

void Mesh::generateNormals(std::vector<Vertex>* vertices, std::vector<GLuint> indices)
{
	for (int i = 0; i < (int)indices.size(); i += 3)
	{
		Vertex* a = &vertices->at(indices.at(i + 0));
		Vertex* b = &vertices->at(indices.at(i + 1));
		Vertex* c = &vertices->at(indices.at(i + 2));

		const glm::vec3 triangleNormal = glm::cross(c->position - a->position, a->position - b->position);

		a->normal += triangleNormal;
		b->normal += triangleNormal;
		c->normal += triangleNormal;
	}

	for (int i = 0; i < (int)vertices->size(); i++)
		vertices->at(i).normal = glm::normalize(vertices->at(i).normal);
}