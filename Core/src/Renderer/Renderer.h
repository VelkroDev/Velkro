#pragma once

#include <glad/glad.h>

#include <vector>
#include <map>

#include "../Window/Window.h"

#include "../API.h"

#include "GLTypes/VAO.h"
#include "GLTypes/VBO.h"
#include "GLTypes/EBO.h"

#include "CustomTypes/Model/Model.h"

namespace Velkro::Renderer
{
	VELKRO_API		bool Init(Window& window);
	VELKRO_API		void Update();
	
	VELKRO_API		void SetViewport(glm::vec2 position, glm::vec2 scale);
}