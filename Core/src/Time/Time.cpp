#include <vlkpch.h>

#include "Time.h"

#include <iostream>

namespace Velkro
{
	float Time::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}

	double Time::GetPreciseTime()
	{
		return glfwGetTime();
	}
}