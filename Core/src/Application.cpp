#include <vlkpch.h>

#include "Application.h"
#include "Renderer/CustomTypes/Texture/Texture.h"

namespace Velkro
{
	Application::Application()
	{
		Window::Init();

		m_Window = Window::Create("Velkro Engine", 800, 600);

		Renderer::Init(m_Window);

		Event::SetEventCallback(OnEvent);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		m_Camera.UpdateEvents(event, m_Window);

		m_EventCallback(event);
	}

	void Application::Run()
	{
		m_AttachCallback();
				
		Shader = Shader::CreateShaderFromFile("assets/Shaders/shader.vertex.glsl", "assets/Shaders/shader.fragment.glsl");;
		
		Model model = Model::CreateModel("assets/Models/map/scene.gltf", VLK_LINEAR);

		while (m_Running && !m_Window.GetClosed())
		{
			Renderer::SetViewport(glm::vec2(0.0f, 0.0f), m_Window.GetScale());
			
			Renderer::Update();

			Event::Update(m_Window);

			m_Camera.UpdateMatrices(Shader, m_Window);

			Shader.Bind();

			model.Render(Shader);

			m_UpdateCallback();

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

	void Application::SetEventCallback(Event::EventCallback eventCallback)
	{
		m_EventCallback = eventCallback;
	}
}