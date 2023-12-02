#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

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

		VELKRO_API		static Window Create(const char* title, int width, int height);

		VELKRO_API		void SetContextCurrent();

		VELKRO_API		void Update();

		VELKRO_API		int GetWidth();
		VELKRO_API		int GetHeight();
		VELKRO_API		glm::vec2 GetScale();

		VELKRO_API		int GetX();
		VELKRO_API		int GetY();
		VELKRO_API		glm::vec2 GetPosition();
		
		VELKRO_API		void SetMousePos(glm::vec2 position);

		VELKRO_API		float GetMouseX();
		VELKRO_API		float GetMouseY();
		VELKRO_API		glm::vec2 GetMousePos();

		VELKRO_API		void SetMouseVisibility(bool visible);

		VELKRO_API		bool GetClosed();

		int width  = 0;
		int height = 0;

		int x = 0;
		int y = 0;

		double mouseX = 0;
		double mouseY = 0;

	private:
		GLFWwindow* m_Window;
	};
}