#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <string>

struct Camera;
class Skybox
{
public:
	Skybox(std::string filename);
	~Skybox();

	void draw();

private:
	Texture* m_texture;
	GLuint m_vertexBufferID;
	GLuint m_vertexArrayID;
	GLuint m_indexBufferID;
};