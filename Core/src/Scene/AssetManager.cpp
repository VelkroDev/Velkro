#include <vlkpch.h>

#include "AssetManager.h"

namespace Velkro
{
	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
	}

	AssetManager AssetManager::CreateAssetManager()
	{
		return AssetManager();
	}

	void AssetManager::UseShader(Shader& shader)
	{
		if (std::find(m_Shaders.begin(), m_Shaders.end(), shader) == m_Shaders.end())
		{
			m_Shaders.push_back(shader);
		}
	}

	void AssetManager::CreateModel(const char* ID, Model& model)
	{
		if (m_Models.find(ID) != m_Models.end())
		{
			m_Models[ID] = model;
		}
	}

	void AssetManager::RenderModel(const char* ID)
	{
		if (m_Models.find(ID) != m_Models.end())
		{
			if (m_Shaders.size() > 0)
			{
				m_Shaders.front().Bind();

				m_Models[ID].Render(m_Shaders.front());
			}
			else
			{
				VLK_CORE_ERROR("Failed to render model {0} as it there aren't any shaders in use.", ID);
			}
		}
		else
		{
			VLK_CORE_ERROR("Failed to render model {0} as it doesn't exist.", ID);
		}
	}

	Model AssetManager::GetModel(const char* ID)
	{
		if (m_Models.find(ID) != m_Models.end())
		{
			return m_Models[ID];
		}
		else
		{
			VLK_CORE_FATAL("Failed to retrieve model {0} as it doesn't exist.", ID);

			return m_Models[ID];
		}
	}
}