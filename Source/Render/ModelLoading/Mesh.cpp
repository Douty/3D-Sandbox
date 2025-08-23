#include "Render/ModelLoading/Mesh.hpp"

using namespace Engine::Render;
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> Indices, std::vector<TextureData> textures):
	m_Vertices(vertices), m_Indices(Indices), m_Textures(textures)
{
	SetupMesh();
}
void Mesh::SetupMesh()
{
	m_VBO = VBO(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
	m_EBO = EBO(m_Indices.data(), m_Indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);
	m_VAO.LinkEBO(m_EBO.GetID());
	m_VAO.LinkAttrib(0, 0, m_VBO.GetID(),3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Position), sizeof(Vertex),0);
	m_VAO.LinkAttrib(1, 0, m_VBO.GetID(), 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal), sizeof(Vertex), 0);
	m_VAO.LinkAttrib(2, 0, m_VBO.GetID(), 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, TexCoords), sizeof(Vertex), 0);



}

void Mesh::Draw(Shader& shader) const
{
	shader.Use();
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		
		std::string number;
		std::string name = m_Textures[i].Type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
		}
		shader.SetInt(("material." + name + number).c_str(), i);
		if (m_Textures[i].Tex) m_Textures[i].Tex->Bind(i);
	}
	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);

}