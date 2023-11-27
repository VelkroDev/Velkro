#pragma once

#include "../../vlkpch.h"

#include "Shader.h"

namespace Velkro
{
	class ShaderManager
	{
	public:
		static void AddShader(const char* ID, Shader shader)
		{
			if (m_Shaders[ID] == shader)
			{
				VLK_CORE_WARN("Shader {0} already exists. Not adding shader to shader manager.", ID);
			}
			else
			{
				m_Shaders[ID] = shader;
			}
		}

		static Shader GetShader(const char* ID)
		{
			if (m_Shaders.find(ID) == m_Shaders.end())
			{
				VLK_CORE_ERROR("Shader {0} doesn't exist. ShaderManager.h - Ln: 24", ID);
			}

			return m_Shaders[ID];
		}

	private:
		static inline std::map<const char*, Shader> m_Shaders;
	};
}