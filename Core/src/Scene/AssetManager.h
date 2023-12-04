#pragma once

#include "../API.h"

#include "../Renderer/CustomTypes/Model/Model.h"

namespace Velkro
{
	class AssetManager
	{
	public:
		VELKRO_API		AssetManager();
		VELKRO_API		~AssetManager();

		VELKRO_API		static AssetManager CreateAssetManager();

		VELKRO_API		void UseShader(Shader& shader);

		VELKRO_API		void CreateModel(const char* ID, Model& model);
		VELKRO_API		void RenderModel(const char* ID);

		VELKRO_API		Model GetModel(const char* ID);

	private:
		std::map<const char*, Model> m_Models;
		std::vector<Shader> m_Shaders;
	};
}