#pragma once

#include "Application.h"
#include "Logging/Log.h"

using namespace Velkro;

class Client
{
public:
	Client(Application* application);

private:
	static void OnAttach();	
	static void OnUpdate();
	static void OnEvent(Event event);
	static void OnDetach();
};