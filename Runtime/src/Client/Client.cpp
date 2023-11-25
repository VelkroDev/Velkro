#include "Client.h"

Client::Client(Application* application)
{
	application->SetAttachCallback(OnAttach);
	application->SetUpdateCallback(OnUpdate);
	application->SetDetachCallback(OnDetach);
}

void Client::OnAttach()
{
	Logger::Init();
}
void Client::OnUpdate()
{
}
void Client::OnDetach()
{
}