#pragma once

#include "../API.h"

#include "AssetManager.h"

namespace Velkro
{
	class Scene
	{
	public:
		VELKRO_API		Scene(const char* ID, AssetManager& assetManager);
		VELKRO_API		~Scene();

		VELKRO_API		static Scene CreateScene(const char* ID, AssetManager& assetManager);

		VELKRO_API		const char* GetID();

	private:
		const char* m_ID;

		AssetManager m_AssetManager;
	};
}