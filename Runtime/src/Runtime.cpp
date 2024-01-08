#include "Client/Client.h"

#include "Application.h"

int main()
{
	Velkro::Application* app = new Application();

	Client client(app);

	app->Run();

	delete app;

	return 0;
}