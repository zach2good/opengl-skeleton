#pragma once

/*
From
http://www.nexcius.net/2014/04/13/loading-meshes-using-assimp-in-opengl/
*/

#include "../common.h"

#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#define NUM_BONES_PER_VEREX 4
#define INVALID_MATERIAL 0xFFFFFFFF

struct BoneInfo
{
	mat4 BoneOffset;
	mat4 FinalTransformation;

	BoneInfo()
	{
		BoneOffset = mat4(0);
		FinalTransformation = mat4(0);
	}
};

struct VertexBoneData
{
	uint IDs[NUM_BONES_PER_VEREX];
	float Weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		Reset();
	};

	void Reset()
	{
	}

	void AddBoneData(uint BoneID, float Weight);
};

class Mesh
{
public:
	struct MeshEntry {
		static enum BUFFERS {
			VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, TANGENT_BUFFER, BITANGENT_BUFFER, BONE_BUFFER, INDEX_BUFFER, BUFFER_COUNT
		};
		GLuint vao;
		GLuint vbo[BUFFER_COUNT];

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