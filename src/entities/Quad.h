#pragma once

#include <SDL.h>

#include <GL\glew.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct VertexFormat {
public:
	VertexFormat::VertexFormat(glm::vec3 pos, glm::vec4 col, glm::vec3 norm, glm::vec2 tex)
		: Position(pos), Color(col), Normal(norm), TexCoords(tex) {}

	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Quad {
public:

	GLuint VBO;
	GLuint VAO;

	Quad::Quad()
	{
		//Generate Position
		std::vector<glm::vec3> pos = std::vector<glm::vec3>();
		pos.push_back(glm::vec3(-0.5, 0.0, -0.5));
		pos.push_back(glm::vec3(0.5, 0.0, -0.5));
		pos.push_back(glm::vec3(-0.5, 0.0, 0.5));
		pos.push_back(glm::vec3(0.5, 0.0, 0.5));

		//Generate Color
		std::vector<glm::vec4> col = std::vector<glm::vec4>();
		col.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
		col.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
		col.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));
		col.push_back(glm::vec4(0.0, 0.0, 1.0, 1.0));

		//Generate Normal
		std::vector<glm::vec3> norm = std::vector<glm::vec3>();
		norm.push_back(glm::vec3(0.0, 1.0, 0.0));
		norm.push_back(glm::vec3(0.0, 1.0, 0.0));
		norm.push_back(glm::vec3(0.0, 1.0, 0.0));
		norm.push_back(glm::vec3(0.0, 1.0, 0.0));

		//Generate TexCoords
		std::vector<glm::vec2> tex = std::vector<glm::vec2>();
		tex.push_back(glm::vec2(0.0, 0.0));
		tex.push_back(glm::vec2(1.0, 0.0));
		tex.push_back(glm::vec2(1.0, 1.0));
		tex.push_back(glm::vec2(0.0, 1.0));

		//Generate Vertices
		std::vector<VertexFormat> vertices = std::vector<VertexFormat>();
		for (int i = 0; i < 4; i++)
		{
			VertexFormat vert = VertexFormat(pos.at(i), col.at(i), norm.at(i), tex.at(i));
			vertices.push_back(vert);
		}

		// Pass to OpenGL
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		// Position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

		// Color attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::Color)));

		// Normal attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::Normal)));

		// TexCoord attribute
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::TexCoords)));

		glBindVertexArray(0); // Unbind VAO
	}
};