#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "Render/Texture.hpp"
#include "Render/VAO.hpp"
#include "Render/VBO.hpp"
#include "Render/EBO.hpp"
#include "Render/Shader.hpp"

namespace Engine::Render {
	class Mesh {


	public:
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};
		struct TextureData {
			std::shared_ptr<Engine::Render::Texture> Tex; 
			std::string Type;                             
			std::string Path;                             

			TextureData(std::shared_ptr<Engine::Render::Texture> tex,
				std::string type,
				std::string path)
				: Tex(std::move(tex)),
				Type(std::move(type)),
				Path(std::move(path)) {
			}

			// Leave copy/move as defaults so vectors/maps can copy it
			TextureData() = default;
			TextureData(const TextureData&) = default;
			TextureData& operator=(const TextureData&) = default;
			TextureData(TextureData&&) = default;
			TextureData& operator=(TextureData&&) = default;
		};
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<TextureData> m_Textures;

		Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> Indices,std::vector<TextureData> textures);
		
		void Draw(Shader& shader) const;

	private:
		VBO m_VBO;
		EBO m_EBO;
		VAO m_VAO;
		void SetupMesh();

		
	};
}