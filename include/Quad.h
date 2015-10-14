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

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Quad::Quad()
	{
		float quadData[] = {
			-0.5f, -0.5f, 0.0f, // pos
			0.0f, 1.0f, 0.0f, 1.0f, // color
			0.0f, 1.0f, 0.0f,   // normal (up in Y direction)
			0.0f, 0.0f,         // tex

			-0.5f, 0.5f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f,

			0.5f, 0.5f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f,

			0.5f, -0.5f, 0.0f,
			1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 0.0f
		};

		int elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		const GLsizei STRIDE = sizeof(float) * 12;

		// VAO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// EBO
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		//  VBO
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, STRIDE * 4, quadData, GL_STATIC_DRAW);

		// Pos
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (const void *)0);

		// Col
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE, (const void *)(sizeof(float) * 3));

		// Norm
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, STRIDE, (const void *)(sizeof(float) * 7));

		// Tex
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, STRIDE, (const void *)(sizeof(float) * 10));

		// Unbind
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Quad::Draw()
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
};