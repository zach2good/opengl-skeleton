#pragma once

#include "../common.h"

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "TextureLoader.h"

class Model
{
public:
	Model() {}
	Model(std::string filename);
	~Model();

	void draw(ShaderProgram shader);

private:
	std::string directory;

	std::vector<Mesh> meshes;	
	std::vector<Texture> texturesLoaded;

	void loadModel(std::string& path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};