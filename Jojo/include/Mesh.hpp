#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <vector>

struct Vertex
{
	Vertex() {};
	Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t);
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct MeshData
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	MeshData(const std::vector<Vertex>&, const std::vector<GLuint>&);
};

class Mesh
{
public:
	Mesh(MeshData);
	Mesh(std::vector<Vertex>);
	Mesh(std::vector<Vertex>, std::vector<GLuint>, bool autoNormals);
	~Mesh();

	void bind() const;
	void draw() const;

	GLuint getVertexBufferID() const;
	GLuint getVertexArrayID() const;
	GLuint getIndexBufferID() const;
	GLuint getNumVertices() const;
	GLuint getNumIndices() const;
	GLfloat getRadius() const;

	static void generateNormals(std::vector<Vertex>* vertices, std::vector<GLuint> indices);

private:
	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&);

	GLuint m_vertexBufferID;
	GLuint m_vertexArrayID;
	GLuint m_indexBufferID;
	GLuint m_numVertices;
	GLuint m_numIndices;
	GLfloat m_radius;
};
