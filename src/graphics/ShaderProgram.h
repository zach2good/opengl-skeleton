#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream> 

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../simplefilewatcher/FileWatcher.h"



class ShaderProgram : public FW::FileWatchListener
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	void UpdateShader();
	void RecompileShader();

	inline void Bind() 
	{ 
		glUseProgram(m_programID); 
	}

	inline void Unbind() 
	{ 
		glBindTexture(GL_TEXTURE_2D, 0);  
		glUseProgram(0); 
	}

	inline GLuint GetId() { return m_programID; }

	inline void SetUniform1i(const char* name, float value)
	{
		glUniform1i(m_UniformLocations[name], value);
	}

	inline void SetUniform1f(const char* name, float value)
	{
		glUniform1f(m_UniformLocations[name], value);
	}

	inline void SetUniform2fv(const char* name, glm::vec2 value)
	{
		glUniform2f(m_UniformLocations[name], value.x, value.y);
	}

	inline void SetUniform3fv(const char* name, glm::vec3 value)
	{
		glUniform3f(m_UniformLocations[name], value.x, value.y, value.z);
	}

	inline void SetUniform4fv(const char* name, glm::mat4 value)
	{
		glUniformMatrix4fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(value));
	}

	inline GLuint GetUniformLocation(const char* name)
	{
		return m_UniformLocations[name];
	}

	inline void SetUniformTexture(GLuint texID, const char* name, GLuint slot)
	{
		glUniform1i(m_UniformLocations[name], slot); // Bind Location
		glActiveTexture(GL_TEXTURE0 + slot); // Activate
		glBindTexture(GL_TEXTURE_2D, texID); // Bind
	}

private:
	GLuint m_Error = 0;

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	GLuint m_newProgramID;
	GLuint m_newVertexShaderID;
	GLuint m_newFragmentShaderID;

	std::string m_Filename;
	FW::FileWatcher fileWatcher;
	FW::WatchID watchID;

	void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename, FW::Action action);

	GLuint LoadShader(const std::string& fileName, GLenum type);

	void GetUniformsAndAttributes(const std::string fileName);

	std::string openFile(std::string input, bool newLine);
	std::vector<std::string> split(const std::string s, const std::string delims);

	std::map <std::string, GLuint> m_UniformLocations;
	std::map <std::string, GLuint> m_AttributeLocations;
};