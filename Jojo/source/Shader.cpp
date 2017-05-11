#include "Shader.hpp"

#include "glm/glm.hpp"

#include <fstream>
#include <sstream>
#include <cassert>

Shader::Shader(std::string vertexShaderFilename, std::string fragmentShaderFilename)
{
	m_vertexShaderID = 0;

	std::ifstream vsFile;
	std::ifstream fsFile;
	vsFile.open(vertexShaderFilename);
	fsFile.open(fragmentShaderFilename);
	if (!(vsFile.is_open() && fsFile.is_open()))
	{
		vsFile.close();
		fsFile.close();
		assert(false && "couldnt find or open vertex shader and/or fragment shader");
	}
	else
	{
		std::stringstream vsBuffer;
		vsBuffer << vsFile.rdbuf();
		std::string vsCodeStr = vsBuffer.str();

		std::stringstream fsBuffer;
		fsBuffer << fsFile.rdbuf();
		std::string fsCodeStr = fsBuffer.str();

		const char* vsCode[1];
		const char* fsCode[1];
		vsCode[0] = vsCodeStr.c_str();
		fsCode[0] = fsCodeStr.c_str();

		// create vertex shader
		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexShaderID, 1, vsCode, 0);
		glCompileShader(m_vertexShaderID);

		// create fragment shader
		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentShaderID, 1, fsCode, 0);
		glCompileShader(m_fragmentShaderID);

		// create program
		m_programID = glCreateProgram();
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);
		glLinkProgram(m_programID);

		// TODO: error handling

		GLint infoLength;
		glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLength);

		GLchar* buffer = new GLchar[infoLength];
		GLsizei bufferSize;
		glGetShaderInfoLog(m_fragmentShaderID, infoLength, &bufferSize, buffer);

		std::stringstream log;
		log << buffer;
		std::string str = log.str();

		GLint status;
		glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &status);
		assert(status > 0 && "couldnt compile vertex shader");
		glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &status);
		assert(status > 0 && "couldnt compile fragment shader");
		glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
		assert(status > 0 && "couldnt link shader program");
	}
}
Shader::~Shader() 
{
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glUseProgram(0);
	glDeleteProgram(m_programID);
}

void Shader::bind() const
{
	glUseProgram(m_programID);
}
void Shader::setVector2(std::string name, const glm::vec2& value) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());
	glUniform2f(uniformLocation, value.x, value.y);
}
void Shader::setVector3(std::string name, const glm::vec3& value) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());
	glUniform3f(uniformLocation, value.x, value.y, value.z);
}
void Shader::setVector4(std::string name, const glm::vec4& value) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());
	glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}
void Shader::setMatrix3(std::string name, const glm::mat3& value) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}
void Shader::setMatrix4(std::string name, const glm::mat4& value) const
{
	GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &value[0][0]);
}