#pragma once

#include <glad/glad.h>

#include <cstdint>

#include "VBO.h"

namespace Velkro
{
	enum VariableType
	{
		VLK_UINT, VLK_INT, 
		VLK_FLOAT, VLK_DOUBLE
	};

	class VAO
	{
	public:
		VAO(uint32_t rendererID, std::vector<uint32_t>& indices)
			: m_RendererID(rendererID), m_Indices(indices)
		{
		}
		VAO()
		{
		}
		~VAO()
		{
		}

		static VAO CreateVAO(std::vector<uint32_t>& indices)
		{
			uint32_t vaoID;
			glGenVertexArrays(1, &vaoID);

			return VAO(vaoID, indices);
		}

		void Bind()
		{
			glBindVertexArray(m_RendererID);
		}

		void UnBind()
		{
			glBindVertexArray(0);
		}

		void LinkAttrib(VBO& VBO, uint32_t index, uint32_t numComponents, VariableType type, size_t stride, void* offset)
		{
			VBO.Bind();

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
			VBO.UnBind();
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
}