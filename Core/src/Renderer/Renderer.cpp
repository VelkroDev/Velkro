#include <vlkpch.h>

#include "Renderer.h"

namespace Velkro
{
	bool Renderer::Init(Window& window, bool multisample, int samples)
	{
		window.SetContextCurrent();

		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_MULTISAMPLE);

			return true;
		}
		else
		{
			VLK_CORE_FATAL("Failed to initialize OpenGL.");

			return false;
		}		
	}

	void Renderer::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetViewport(glm::vec2 position, glm::vec2 scale)
	{
		glViewport(static_cast<GLint>(position.x), static_cast<GLint>(position.y), 
			       static_cast<GLint>(scale.x),    static_cast<GLint>(scale.y));
	}
}