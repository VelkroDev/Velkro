#include <vlkpch.h>

#include "Renderer.h"

namespace Velkro
{
	bool Renderer::Init(Window& window)
	{
		window.SetContextCurrent();

		return gladLoadGL();
	}

	void Renderer::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
}