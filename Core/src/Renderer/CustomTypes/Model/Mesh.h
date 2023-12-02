#include "../../GLTypes/VAO.h"
#include "../../GLTypes/VBO.h"
#include "../../GLTypes/EBO.h"

#include "../../CustomTypes/Texture/Texture.h"

#include <vector>

#include <glm/gtc/type_ptr.hpp>

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

		Mesh(VAO& VAO, VBO& VBO, EBO& EBO, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures)
			: MeshVAO(VAO), MeshVBO(VBO), MeshEBO(EBO), Vertices(vertices), Indices(indices), Textures(textures)
		{
		}

		static Mesh CreateMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures)
		{
			VAO VAO = VAO::CreateVAO(indices);
			VBO VBO = VBO::CreateVBO();
			EBO EBO = EBO::CreateEBO();

			VAO.Bind();

			VBO.Bind();

			VBO.SetData(vertices, VLK_DYNAMIC);

			EBO.Bind();

			EBO.SetData(indices, VLK_DYNAMIC);

			VAO.LinkAttrib(VBO, 0, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
			VAO.LinkAttrib(VBO, 1, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			VAO.LinkAttrib(VBO, 2, 3, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, colour));
			VAO.LinkAttrib(VBO, 3, 2, VLK_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));

			VBO.UnBind();
			VAO.UnBind();
			EBO.UnBind();

			return Mesh(VAO, VBO, EBO, vertices, indices, textures);
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

			MeshVAO.Render();
		}

		VAO MeshVAO;
		VBO MeshVBO;
		EBO MeshEBO;

		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;

		std::vector<Texture> Textures;		
	};
}