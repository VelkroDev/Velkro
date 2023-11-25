#include <vlkpch.h>

#include "Application.h"

namespace Velkro
{
	Application::Application()
	{
		Window::Init();

		m_Window = Window::NewWindow("Velkro Engine", 800, 600);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_AttachCallback();
		
		while (m_Running && !m_Window.GetClosed())
		{
			m_Window.Update();

			m_UpdateCallback();	
		}

		m_Running = false;

		m_DetachCallback();
	}	
	
	/* CALLBACKS */
	void Application::SetAttachCallback(AttachCallback attachCallback)
	{
		m_AttachCallback = attachCallback;
	}
	void Application::SetUpdateCallback(UpdateCallback updateCallback)
	{
		m_UpdateCallback = updateCallback;
	}
	void Application::SetDetachCallback(DetachCallback detachCallback)
	{
		m_DetachCallback = detachCallback;
	}
}