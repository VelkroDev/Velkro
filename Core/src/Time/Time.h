#pragma once

#include "../API.h"

#include <GLFW/glfw3.h>

namespace Velkro
{
	class Time
	{
	public:
		VELKRO_API		static float GetTime();
		VELKRO_API		static double GetPreciseTime();
	};
}