#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "../Buffer.h"
#include "../Texture/Texture.h"

namespace Velkro
{
	class Mesh
	{
	public:
		Mesh()
		{
		}

		~Mesh()
		{
		}

		Mesh(VertexArray& vertexArray, VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures)
			: MeshVertexArray(vertexArray), MeshVertexBuffer(vertexBuffer), MeshIndexBuffer(indexBuffer), Vertices(vertices), Indices(indices), Textures(textures)
		{
		}

		static Mesh CreateMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures)
		{
			VertexArray vertexArray = VertexArray::CreateVertexArray(indices);
			VertexBuffer vertexBuffer = VertexBuffer::CreateVertexBuffer();
			IndexBuffer indexBuffer = IndexBuffer::CreateIndexBuffer();

			vertexArray.Bind();

			vertexBuffer.Bind();

			vertexBuffer.SetData(vertices, VLK_DYNAMIC);

			indexBuffer.Bind();

			indexBuffer.SetData(indices, VLK_DYNAMIC);

			vertexArray.LinkAttrib(vertexBuffer, 0, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
			vertexArray.LinkAttrib(vertexBuffer, 1, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			vertexArray.LinkAttrib(vertexBuffer, 2, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, colour));
			vertexArray.LinkAttrib(vertexBuffer, 3, 2, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));
			vertexArray.LinkAttrib(vertexBuffer, 4, 1, VLK_INT  , sizeof(Vertex), (void*)offsetof(Vertex, textureID));

			vertexBuffer.UnBind();
			vertexArray.UnBind();
			indexBuffer.UnBind();

			return Mesh(vertexArray, vertexBuffer, indexBuffer, vertices, indices, textures);
		}

		void Render(Shader& shader, glm::mat4 matrix)
		{
			for (int i = 0; i < Textures.size(); i++)
			{
				std::string type;
				
				if (Textures[i].GetTextureType() == VLK_DIFFUSE)
				{
					type = "diffuse";
				}
				else if (Textures[i].GetTextureType() == VLK_SPECULAR)
				{
					type = "specular";
				}

				Textures[i].SetTextureUnit(shader, type.c_str(), i);
			}

			glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "u_ModelMatrix"), 1, GL_FALSE, glm::value_ptr(matrix));

			MeshVertexArray.Render();
		}

		VertexArray MeshVertexArray;
		VertexBuffer MeshVertexBuffer;
		IndexBuffer MeshIndexBuffer;

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;

		std::vector<Texture> Textures;		
	};
}