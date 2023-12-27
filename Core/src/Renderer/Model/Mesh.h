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

			vertexBuffer.UnBind();
			vertexArray.UnBind();
			indexBuffer.UnBind();

			return Mesh(vertexArray, vertexBuffer, indexBuffer, vertices, indices, textures);
		}

		void Render(Shader& shader, glm::mat4 matrix, glm::vec3 translation = glm::vec3(0.0f), 	glm::vec3 scale = glm::vec3(1.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
		{
			uint32_t diffuseCount = 0;
			uint32_t specularCount = 0;

			for (int i = 0; i < Textures.size(); i++)
			{
				std::string count;
				std::string type;

				if (Textures[i].GetTextureType() == VLK_DIFFUSE)
				{
					type = "diffuse";

					count = std::to_string(diffuseCount++);
				}
				else if (Textures[i].GetTextureType() == VLK_SPECULAR)
				{
					type = "specular";

					count = std::to_string(specularCount++);
				}

				Textures[i].SetTextureUnit(shader, (type + count).c_str(), i);
			}

			glm::mat4 translationMat = glm::mat4(1.0f);
			glm::mat4 scaleMat = glm::mat4(1.0f);
			glm::mat4 rotationMat = glm::mat4(1.0f);

			translationMat = glm::translate(translationMat, translation);
			scaleMat = glm::scale(scaleMat, scale);
			rotationMat = glm::mat4_cast(rotation);

			glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "u_TranslationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMat));			
			glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "u_ScaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMat));
			glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "u_RotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMat));

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