#include "ShaderProgram.h"

using namespace std;

ShaderProgram::ShaderProgram(const std::string& fileName)
{
	// save filename
	m_Filename = fileName;

	// Load shaders from file
	m_vertexShaderID = LoadShader(m_Filename + ".vert", GL_VERTEX_SHADER);
	m_fragmentShaderID = LoadShader(m_Filename + ".frag", GL_FRAGMENT_SHADER);

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

	// Set Watch
	watchID = fileWatcher.addWatch("../res/shaders/", this, true);

	GetUniformsAndAttributes(m_Filename + ".vert");
	GetUniformsAndAttributes(m_Filename + ".frag");
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

void ShaderProgram::UpdateShader()
{
	fileWatcher.update();
}

void ShaderProgram::handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
	FW::Action action)
{
	std::cout << "DIR CHANGE " << dir  + filename + " has event " << action << std::endl;
	RecompileShader();
}

void ShaderProgram::RecompileShader()
{
	// Load shaders from file
	m_newVertexShaderID = LoadShader(m_Filename + ".vert", GL_VERTEX_SHADER);
	m_newFragmentShaderID = LoadShader(m_Filename + ".frag", GL_FRAGMENT_SHADER);

	// Create shader program
	m_newProgramID = glCreateProgram();

	// Attach the shaders to the program
	glAttachShader(m_newProgramID, m_newVertexShaderID);
	glAttachShader(m_newProgramID, m_newFragmentShaderID);

	// Link the program
	glLinkProgram(m_newProgramID);
	glValidateProgram(m_newProgramID);

	// Check validation status
	GLint status;
	glGetProgramiv(m_newProgramID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetProgramiv(m_newProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_newProgramID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not validate program \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}
	else
	{
		std::cout << "Compilation successful, using new shader" << std::endl;
		m_programID = m_newProgramID;
	}
}

std::string ShaderProgram::openFile(std::string input, bool newLine)
{
	string temp;
	string content;
	ifstream file(input);
	if (file.is_open())
	{
		while (getline(file, temp))
		{
			content += temp + (newLine ? "\n" : "");
		}
		file.close();
	}
	else
	{
		printf("Unable to open file: %s\n", input.c_str());
	}

	return content;
}

std::vector<std::string> ShaderProgram::split(const std::string s, const std::string delims)
{
	std::vector<std::string> result;
	std::string::size_type pos = 0;
	while (std::string::npos != (pos = s.find_first_not_of(delims, pos))) {
		auto pos2 = s.find_first_of(delims, pos);
		result.emplace_back(s.substr(pos, std::string::npos == pos2 ? pos2 : pos2 - pos));
		pos = pos2;
	}
	return result;
}

void ShaderProgram::GetUniformsAndAttributes(const std::string fileName)
{
	auto file_lines = split(openFile(fileName, false), ";");

	printf("\nGetting Shader Uniforms: %s\n", fileName.c_str());
	for (auto str : file_lines)
	{
		if (str.find("uniform") != std::string::npos)
		{
			auto a = split(str, " ");
			printf("  -Found uniform: %s of type %s\n", a[2].c_str(), a[1].c_str());

			m_UniformLocations[a[2]] = glGetUniformLocation(GetId(), a[2].c_str());
		}
	}

	printf("\nGetting Shader Attributes: %s\n", fileName.c_str());
	for (auto str : file_lines)
	{
		if (str.find("attribute") != std::string::npos)
		{
			auto a = split(str, " ");
			printf("  -Found attribute: %s of type %s\n", a[2].c_str(), a[1].c_str());

			m_AttributeLocations[a[2]] = glGetAttribLocation(GetId(), a[2].c_str());
		}
	}
}