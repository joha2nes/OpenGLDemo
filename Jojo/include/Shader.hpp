#pragma once
#include "GL/glew.h"
#include "glm\glm.hpp"
#include <string>

class Shader
{
private:
	Shader(const Shader&);
	Shader& operator=(const Shader&);

public:
	Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename);
	~Shader();

	void bind() const;

	void setVector2(std::string name, const glm::vec2& value) const;
	void setVector3(std::string name, const glm::vec3& value) const;
	void setVector4(std::string name, const glm::vec4& value) const;
	void setMatrix3(std::string name, const glm::mat3& value) const;
	void setMatrix4(std::string name, const glm::mat4& value) const;

protected:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
};