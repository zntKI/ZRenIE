#pragma once

#include "Trait.hpp"

#include "Mesh.hpp"
#include "../../Utility/Shader.hpp"

#include "../UI/Panels/Traits/TraitsViews/TModelView.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

uint32_t TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class TModel : public Trait
{
	friend class TTransformView;

public:
	TModel(const std::string& modelFilePath);
	void Draw(const glm::mat4& mvpMatrix);

	std::vector<std::shared_ptr<Mesh>> m_Meshes;

	void Render() override;

private:
	std::string m_Directory;
	std::string m_ModelName;

	TModelView modelView;

private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
};