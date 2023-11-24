#pragma once

#include "Application.h"

using namespace Velkro;

class Client
{
public:
	Client(Application* application);

private:
	static void Attach();	
	static void Update();
	static void Detach();
};