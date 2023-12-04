#include <vlkpch.h>

#include "Scene.h"

namespace Velkro
{
	Scene::Scene(const char* ID, AssetManager& assetManager)
		: m_ID(ID), m_AssetManager(assetManager)
	{
	}
	Scene::~Scene()
	{
	}

	Scene Scene::CreateScene(const char* ID, AssetManager& assetManager)
	{
		return Scene(ID, assetManager);
	}

	const char* Scene::GetID()
	{
		return m_ID;
	}
}