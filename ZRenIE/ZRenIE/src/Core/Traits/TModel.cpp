#include "TModel.hpp"

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include <memory>

TModel::TModel(const char* path)
{
	loadModel(path);
}

void TModel::Draw()
{
	for (auto& mesh : m_Meshes)
	{
		mesh->Draw();
	}
}

void TModel::loadModel(std::string path)
{
	Assimp::Importer importer;
	// Read all the data into the aiScene
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
		!scene->mRootNode)
	{
		std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void TModel::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Mesh> TModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		glm::vec3 vector;

		// position
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.m_Position = vector;

		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.m_Normal = vector;

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.m_TexCoords = vec;
		}
		else
			vertex.m_TexCoords = glm::vec2(0.f, 0.f);


		vertices.push_back(vertex);
	}

	// process indices
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return std::make_shared<Mesh>(vertices, indices);
}

uint32_t TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	uint32_t textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}