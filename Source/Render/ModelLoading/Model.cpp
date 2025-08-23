#include "Render/ModelLoading/Model.hpp"
#include <iostream>


using namespace Engine::Render;

Model::Model(const std::string& path)
{
	LoadModel(path);
}
void Model::Draw(Shader& shader) const
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
		m_Meshes[i].Draw(shader);
}
void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Engine::Render::Mesh::Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Engine::Render::Mesh::TextureData> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Engine::Render::Mesh::Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;


		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;


		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Engine::Render::Mesh::TextureData> diffuseMaps = LoadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Engine::Render::Mesh::TextureData> specularMaps = LoadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}



std::vector<Engine::Render::Mesh::TextureData> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	
	std::vector<Engine::Render::Mesh::TextureData> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString rel;
		if (mat->GetTexture(type, i, &rel) != AI_SUCCESS) continue;

		std::string fullPath = m_Directory + "/" + std::string(rel.C_Str());

		bool found = false;
		for (unsigned int j = 0; j < m_Textures_loaded.size(); ++j) {
			if (m_Textures_loaded[j].Path == fullPath && m_Textures_loaded[j].Type == typeName) {
				textures.push_back(m_Textures_loaded[j]); // copy from cache
				found = true;
				break;
			}
		}
		if (!found) {
			// load new, add to both the result and the cache
			auto tex = std::make_shared<Texture>(fullPath.c_str());
			m_Textures_loaded.emplace_back(tex, typeName, fullPath);
			textures.push_back(m_Textures_loaded.back());
		}
	}
	
	return textures;

}


