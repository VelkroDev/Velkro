#include "Client.h"

Client::Client(Application* application)
{
	application->SetAttachCallback(Attach);
	application->SetUpdateCallback(Update);
	application->SetDetachCallback(Detach);
}

void Client::Attach()
{
}
void Client::Update()
{
}
void Client::Detach()
{

}