#pragma once

/*
From
http://www.nexcius.net/2014/04/13/loading-meshes-using-assimp-in-opengl/
*/

#include "common.h"

#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

class Mesh
{
public:
	struct MeshEntry {
		static enum BUFFERS {
			VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
		};
		GLuint vao;
		GLuint vbo[4];

		unsigned int elementCount;

		MeshEntry(aiMesh *mesh);
		~MeshEntry();

		void load(aiMesh *mesh);
		void render();
	};

	std::vector<MeshEntry*> meshEntries;

public:
	Mesh(const char *filename);
	~Mesh(void);

	void render();
};