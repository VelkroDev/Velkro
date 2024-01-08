#include <vlkpch.h>

#include "Application.h"

namespace Velkro
{
	Application::Application()
	{
		Window::Init(true, 128);

		m_Window = Window::Create("Velkro Engine", 800, 600);

		Renderer::Init(m_Window);

		Event::SetEventCallback(OnEvent);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		m_EventCallback(event, m_Window);
	}

	void Application::Run()
	{
		m_AttachCallback(m_Window);
				
		while (m_Running && !m_Window.GetClosed())
		{
			Renderer::SetViewport(glm::vec2(0.0f, 0.0f), m_Window.GetScale());
			
			Renderer::Update();

			Event::Update(m_Window);

			m_UpdateCallback(m_Window);

			m_Window.Update();
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

	void Application::SetEventCallback(AppEventCallback eventCallback)
	{
		m_EventCallback = eventCallback;
	}
}