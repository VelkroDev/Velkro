#pragma once

#include <glad/glad.h>

#include <cstdint>

namespace Velkro
{
	struct Vertex
	{
	public:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 colour;
		glm::vec2 textureCoord;

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 colour, glm::vec2 textureCoord)
			: position(position), normal(normal), colour(colour), textureCoord(textureCoord)
		{
		}
	};

	enum VLK_DATA_USAGE
	{
		VLK_STATIC, VLK_STREAM, VLK_DYNAMIC
	};

	class VBO
	{
	public:
		VBO(uint32_t rendererID)
			: m_RendererID(rendererID)
		{
		}
		VBO()
		{
		}
		~VBO()
		{
		}

		static VBO CreateVBO()
		{
			uint32_t vboID;
			glGenBuffers(1, &vboID);

			return VBO(vboID);
		}

		void SetData(std::vector<Vertex> vertices, VLK_DATA_USAGE dataUsage)
		{
			GLenum glDataUsage = GL_DYNAMIC_DRAW;

			switch (dataUsage)
			{
				case VLK_DYNAMIC:
				{
					glDataUsage = GL_DYNAMIC_DRAW;

					break;
				}
				case VLK_STATIC:
				{
					glDataUsage = GL_STATIC_DRAW;

					break;
				}
				case VLK_STREAM:
				{
					glDataUsage = GL_STREAM_DRAW;

					break;
				}
			}

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), glDataUsage);
		}

		void Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		}

		void UnBind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		uint32_t& GetRendererID()
		{
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}