#include "Client.h"

Client::Client(Application* application)
{
	application->SetAttachCallback(OnAttach);
	application->SetUpdateCallback(OnUpdate);
	application->SetDetachCallback(OnDetach);

	application->SetEventCallback(OnEvent);
}

void Client::OnAttach()
{
	Logger::Init();
}

void Client::OnUpdate()
{
	
}

void Client::OnEvent(Event event)
{
}

void Client::OnDetach()
{
}