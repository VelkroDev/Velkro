#pragma once

#include <glad/glad.h>

#include <vector>
#include <map>

#include "../Window/Window.h"

#include "../API.h"

#include "Model/Model.h"

namespace Velkro::Renderer
{
	VELKRO_API		bool Init(Window& window, bool multisample = true, int samples = 8);
	VELKRO_API		void Update();
	
	VELKRO_API		void SetViewport(glm::vec2 position, glm::vec2 scale);
}