#pragma once
#include "Mesh.hpp"
#include <assimp/scene.h>      
#include <assimp/Importer.hpp>  
#include <assimp/postprocess.h> 
namespace Engine::Render
{
	class Model {
	public:
		Model(const std::string& path);
		void Draw(Shader& shader) const;

	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Engine::Render::Mesh::TextureData> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
		std::vector<Engine::Render::Mesh::TextureData> m_Textures_loaded;

	};
}