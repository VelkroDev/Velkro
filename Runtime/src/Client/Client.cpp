#include "Client.h"

Client::Client(Application* application)
{
	application->SetAttachCallback(OnAttach);
	application->SetUpdateCallback(OnUpdate);
	application->SetDetachCallback(OnDetach);

	application->SetEventCallback(OnEvent);
}

void Client::OnAttach(Window& window)
{
	Logger::Init();
	
	gladLoadGL();

	m_Shader = Shader::CreateShaderFromFile("assets/Shaders/shader.vertex.glsl", "assets/Shaders/shader.fragment.glsl");

	m_Model = Model::CreateModel("assets/Models/velkroCube/untitled.gltf", VLK_LINEAR);
}

void Client::OnUpdate(Window& window)
{
	m_Camera.UpdateMatrices(m_Shader, window.GetScale());

	m_Shader.Bind();

	m_Model.Render(m_Shader);
}

void Client::OnEvent(Event event, Window& window)
{
	m_Camera.UpdateEvents(event, window);
}

void Client::OnDetach()
{
}