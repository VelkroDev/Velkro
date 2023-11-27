#pragma once

#include <GLFW/glfw3.h>

#include "../API.h"

namespace Velkro
{
	class Window
	{
	public:
		VELKRO_API		friend class Event;

		VELKRO_API		static bool Init();

		VELKRO_API		Window();
		VELKRO_API		~Window();

		VELKRO_API		static Window NewWindow(const char* title, int width, int height);

		VELKRO_API		void SetContextCurrent();

		VELKRO_API		void Update();

		VELKRO_API		int GetWidth();
		VELKRO_API		int GetHeight();

		VELKRO_API		int GetX();
		VELKRO_API		int GetY();
		
		VELKRO_API		bool GetClosed();

		int width  = 0;
		int height = 0;

		int x = 0;
		int y = 0;

	private:
		GLFWwindow* m_Window;
	};
}