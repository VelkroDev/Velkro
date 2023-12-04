#include <vlkpch.h>

#include "Window.h"

namespace Velkro
{
	bool Window::Init(bool multisample, int samples)
	{
		if (glfwInit())
		{
			if (multisample)
			{
				glfwWindowHint(GLFW_SAMPLES, 32);
			}
			
			glfwWindowHint(GLFW_PLATFORM, GLFW_ANY_PLATFORM);

			return true;
		}
		else
		{
			VLK_CORE_ERROR("Failed to initialize window system.");

			return false;
		}
	}

	Window::Window()
	{
	}
	Window::~Window()
	{
	}

	Window Window::Create(const char* title, int width, int height)
	{
		Window window;

		window.m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		window.width = width;
		window.height = height;

		return window;
	}

	void Window::SetContextCurrent()
	{
		glfwMakeContextCurrent(m_Window);
	}

	void Window::Update()
	{
		glfwGetWindowSize(m_Window, &width, &height);
		glfwGetWindowPos(m_Window, &x, &y);

		glfwGetCursorPos(m_Window, &mouseX, &mouseY);

		glfwSwapBuffers(m_Window);

		glfwPollEvents();
	}

	int Window::GetWidth()
	{
		return width;
	}
	int Window::GetHeight()
	{
		return height;
	}
	glm::vec2 Window::GetScale()
	{
		return glm::vec2(width, height);
	}

	int Window::GetX()
	{
		return x;
	}
	int Window::GetY()
	{
		return y;
	}
	glm::vec2 Window::GetPosition()
	{
		return glm::vec2(x, y);
	}

	float Window::GetMouseX()
	{
		return static_cast<float>(mouseX);
	}
	float Window::GetMouseY()
	{
		return static_cast<float>(mouseY);
	}
	glm::vec2 Window::GetMousePos()
	{
		return glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	void Window::SetMousePos(glm::vec2 position)
	{
		glfwSetCursorPos(m_Window, position.x, position.y);
	}

	void Window::SetMouseVisibility(bool visible)
	{
		if (visible)
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}		
	}

	bool Window::GetClosed()
	{
		return glfwWindowShouldClose(m_Window);
	}
}