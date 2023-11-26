#include <vlkpch.h>

#include "Renderer.h"

namespace Velkro
{
	bool Renderer::Init()
	{
		return gladLoadGL();
	}
}