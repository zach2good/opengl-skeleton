#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& fileName)
{
	// Load shaders from file
	m_vertexShaderID = LoadShader(fileName + ".vert", GL_VERTEX_SHADER);
	m_fragmentShaderID = LoadShader(fileName + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	m_programID = glCreateProgram();

	// Attach the shaders to the program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	// Link the program
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	// Check validation status
	GLint status;
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not validate program \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;

		system("PAUSE");
	}
}


ShaderProgram::~ShaderProgram()
{
	// Make sure we are not using this shader
	Unbind();
	// Detach the shaders from the program
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	// Delete the shaders
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	// Delete the program
	glDeleteProgram(m_programID);
}

GLuint ShaderProgram::LoadShader(const std::string& fileName, GLenum type)
{
	// Open the file as read only
	FILE* file;
	file = fopen(fileName.c_str(), "r");
	if (file == NULL)
	{
		printf("Failed to open: %s\n", fileName.c_str());
	}

	// Create temp variables
	std::string source;
	char buffer[1024];
	while (fgets(buffer, 1024, file) != NULL)
	{
		source.append(buffer);
	}
	fclose(file);

	// Create shader ID
	GLuint shaderID = glCreateShader(type);

	// Prepare source for OpenGL
	const GLchar* sourceStrings[1];
	GLint sourceLengths[1];
	sourceStrings[0] = source.c_str();
	sourceLengths[0] = source.length();

	// Load source to OpenGL and compile
	glShaderSource(shaderID, 1, sourceStrings, sourceLengths);
	glCompileShader(shaderID);

	// Check compile status
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not compile shader \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}

	return shaderID;
}
