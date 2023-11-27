#pragma once

#include <glad/glad.h>

#include <cstdint>

namespace Velkro
{
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

		static VBO CreateVBO(float* vertices, size_t verticesSize, VLK_DATA_USAGE dataUsage = VLK_DYNAMIC)
		{
			uint32_t vboID;
			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);

			if (dataUsage == VLK_STATIC)
			{
				glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
			}
			else if (dataUsage == VLK_STREAM)
			{
				glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STREAM_DRAW);
			}
			else if (dataUsage == VLK_DYNAMIC)
			{
				glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_DYNAMIC_DRAW);
			}

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return VBO(vboID);
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