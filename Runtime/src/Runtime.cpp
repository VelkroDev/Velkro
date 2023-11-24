#include "Client/Client.h"

#include "Application.h"

int main()
{
	Velkro::Application* app = new Application();

	Client* client = new Client(app);

	app->Run();

	delete client;
	delete app;

	return 0;
}