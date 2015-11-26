#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	inline void Bind() { glUseProgram(m_programID); }
	inline void Unbind() { glUseProgram(0); }
	inline GLuint GetId() { return m_programID; }

	inline void SetUniform1i(const char* name, float value)
	{
		glUniform1i(glGetUniformLocation(GetId(), name), value);
	}

	inline void SetUniform1f(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(GetId(), name), value);
	}

	inline void SetUniform2fv(const char* name, glm::vec2 value)
	{
		GLint location = glGetUniformLocation(GetId(), name);
		glUniform2f(location, value.x, value.y);
	}

	inline void SetUniform3fv(const char* name, glm::vec3 value)
	{
		GLint location = glGetUniformLocation(GetId(), name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	inline void SetUniform4fv(const char* name, glm::mat4 value)
	{
		GLint location = glGetUniformLocation(GetId(), name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	inline void SetUniformTexture(GLuint texID, const char* name, GLuint slot)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glUniform1i(glGetUniformLocation(GetId(), name), slot);
	}

	

private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	GLuint LoadShader(const std::string& fileName, GLenum type);
};