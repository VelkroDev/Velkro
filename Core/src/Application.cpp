#include <vlkpch.h>

#include "Application.h"

namespace Velkro
{
	Application::Application()
	{
		Window::Init();

		m_Window = Window::NewWindow("Velkro Engine", 800, 600);

		Renderer::Init(m_Window);

		Event::SetEventCallback(OnEvent);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event event)
	{
		m_EventCallback(event);
	}

	void Application::Run()
	{
		m_AttachCallback();
		
		Shader Shader = Shader::CreateShaderFromFile("assets/Shaders/shader.vertex.glsl", "assets/Shaders/shader.fragment.glsl");;

		VAO VAO;
		VBO VBO;
		EBO EBO;

		float vertices[] =
		{
			0.5f, 0.5f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.0f, 0.0f, 0.0f,
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 1,
		};		

		VAO = VAO::CreateVAO();

		VAO.Bind();

		VBO = VBO::CreateVBO(vertices, sizeof(vertices));

		EBO = EBO::CreateEBO(indices, sizeof(indices));

		VBO.UnBind();
		VAO.UnBind();
		EBO.UnBind();

		while (m_Running && !m_Window.GetClosed())
		{
			glViewport(0, 0, m_Window.GetWidth(), m_Window.GetHeight());

			Renderer::Update();

			Event::Update(m_Window);

			Shader.Bind();
			VAO.Bind();
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

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