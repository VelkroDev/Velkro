#include "Client.h"

Client::Client(Application* application)
{
	application->SetAttachCallback(OnAttach);
	application->SetUpdateCallback(OnUpdate);
	application->SetDetachCallback(OnDetach);

	application->SetEventCallback(OnEvent);

	gladLoadGL();
}

void Client::OnAttach(Window& window)
{
	Logger::Init();

	m_Shader = Shader::CreateShaderFromFile("assets/Shaders/shader.vertex.glsl", "assets/Shaders/shader.fragment.glsl");

	model = Model::CreateModel("assets/Models/crates/crates.gltf", VLK_LINEAR);
}

void Client::OnUpdate(Window& window)
{
	m_Camera.UpdateMatrices(m_Shader, window.GetScale());
	
	m_Shader.Bind();

	model.Render(m_Shader);
}

void Client::OnEvent(Event event, Window& window)
{
	m_Camera.UpdateEvents(event, window);
}

void Client::OnDetach()
{
}