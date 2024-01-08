#pragma once

#include <glad/glad.h>

#include <vlkpch.h>

namespace Velkro
{
	struct Vertex
	{
	public:
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 colour;
		glm::vec2 textureCoord;
		uint32_t textureID = 0;

		Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 colour, glm::vec2 textureCoord, uint32_t textureID = -1)
			: position(position), normal(normal), colour(colour), textureCoord(textureCoord), textureID(textureID)
		{
		}
	};

	enum VariableType
	{
		VLK_UINT, VLK_INT,
		VLK_FLOAT, VLK_DOUBLE
	};

	enum DataUsage
	{
		VLK_STATIC, VLK_STREAM, VLK_DYNAMIC
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t rendererID)
			: m_RendererID(rendererID)
		{
		}
		VertexBuffer()
		{
		}
		~VertexBuffer()
		{
		}

		static VertexBuffer CreateVertexBuffer()
		{
			uint32_t vertexBufferID;
			glGenBuffers(1, &vertexBufferID);

			VertexBuffer vertexBuffer(vertexBufferID);

			return vertexBuffer;
		}

		void SetData(std::vector<Vertex> vertices, DataUsage dataUsage)
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

		void Destroy()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

	private:
		uint32_t m_RendererID;
	};

	class VertexArray
	{
	public:
		VertexArray(uint32_t rendererID, std::vector<uint32_t>& indices)
			: m_RendererID(rendererID), m_Indices(indices)
		{
		}
		VertexArray()
		{
		}
		~VertexArray()
		{
		}

		static VertexArray CreateVertexArray(std::vector<uint32_t>& indices)
		{
			uint32_t vertexArrayID;
			glGenVertexArrays(1, &vertexArrayID);

			return VertexArray(vertexArrayID, indices);
		}

		void Bind()
		{
			glBindVertexArray(m_RendererID);
		}

		void UnBind()
		{
			glBindVertexArray(0);
		}

		void LinkAttrib(VertexBuffer& vertexBuffer, uint32_t index, uint32_t numComponents, VariableType type, size_t stride, void* offset)
		{
			vertexBuffer.Bind();

			GLenum glType = GL_FLOAT;

			switch (type)
			{
			case VLK_UINT:
			{
				glType = GL_UNSIGNED_INT;

				break;
			}
			case VLK_INT:
			{
				glType = GL_INT;

				break;
			}
			case VLK_FLOAT:
			{
				glType = GL_FLOAT;

				break;
			}
			case VLK_DOUBLE:
			{
				glType = GL_DOUBLE;

				break;
			}
			}

			glVertexAttribPointer(index, numComponents, glType, GL_FALSE, static_cast<GLsizei>(stride), offset);
			glEnableVertexAttribArray(index);
			vertexBuffer.UnBind();
		}

		void Render()
		{
			Bind();

			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);

			UnBind();
		}

		uint32_t& GetRendererID()
		{
			return m_RendererID;
		}

		void Destroy()
		{
			glDeleteVertexArrays(1, &m_RendererID);
		}

	private:
		uint32_t m_RendererID;

		std::vector<uint32_t> m_Indices;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t rendererID)
			: m_RendererID(rendererID)
		{
		}
		IndexBuffer()
		{
		}
		~IndexBuffer()
		{
		}

		static IndexBuffer CreateIndexBuffer()
		{
			uint32_t indexBufferID;

			glGenBuffers(1, &indexBufferID);

			return IndexBuffer(indexBufferID);
		}

		void SetData(std::vector<uint32_t> indices, DataUsage dataUsage = VLK_DYNAMIC)
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
			default:
			{
				VLK_CORE_ERROR("Invalid data usage set for Element Array Buffer. Reverting to VLK_DYNAMIC.");

				break;
			}
			}

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), glDataUsage);
		}

		void Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		}

		void UnBind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		uint32_t& GetRendererID()
		{
			return m_RendererID;
		}

		void Destroy()
		{
			glDeleteBuffers(1, &m_RendererID);
		}

	private:
		uint32_t m_RendererID;
	};
}