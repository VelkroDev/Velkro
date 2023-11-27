#pragma once

#include <glad/glad.h>

#include <cstdint>

namespace Velkro
{
	class VAO
	{
	public:
		VAO(uint32_t rendererID)
			: m_RendererID(rendererID)
		{
		}
		VAO()
		{
		}

		static VAO CreateVAO()
		{
			uint32_t vaoID;
			glGenVertexArrays(1, &vaoID);

			return VAO(vaoID);
		}

		void Bind()
		{
			glBindVertexArray(m_RendererID);
		}

		void UnBind()
		{
			glBindVertexArray(0);
		}

		uint32_t& GetRendererID()
		{
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}