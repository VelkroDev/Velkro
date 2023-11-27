#include <vlkpch.h>

#include "Window.h"

namespace Velkro
{
	bool Window::Init()
	{
		return glfwInit();
	}

	Window::Window()
	{
	}
	Window::~Window()
	{
	}

	Window Window::NewWindow(const char* title, int width, int height)
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

	int Window::GetX()
	{
		return x;
	}
	int Window::GetY()
	{
		return y;
	}

	bool Window::GetClosed()
	{
		return glfwWindowShouldClose(m_Window);
	}
}