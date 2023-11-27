#pragma once

#include <glad/glad.h>

#include "../Window/Window.h"
#include "../API.h"

#include "Renderer3D.h"

namespace Velkro
{
	class Renderer
	{
	public:
		VELKRO_API		static bool Init(Window& window);
		VELKRO_API		static void Update();
	};
}