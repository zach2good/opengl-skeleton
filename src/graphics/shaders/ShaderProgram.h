#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	inline void Bind() { glUseProgram(m_programID); }
	inline void Unbind() { glUseProgram(0); }
	inline GLuint GetId() { return m_programID; }

	inline void SetUniformf(const char* name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	GLuint LoadShader(const std::string& fileName, GLenum type);
protected:
	void BindAttribute(int attribute, const std::string& variableName);
	GLuint GetUniformLocation(const std::string& name);
	void LoadFloat(GLuint& location, float& value);
	void LoadVector(GLuint& location, glm::vec3& value);
	void LoadBool(GLuint& location, bool& value);
	void LoadMatrix4(GLuint& location, glm::mat4& matrix);
};

#endif // SHADERPROGRAM_H