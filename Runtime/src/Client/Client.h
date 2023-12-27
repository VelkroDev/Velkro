#pragma once

#include "Application.h"

using namespace Velkro;

class Client
{
public:
	Client(Application* application);

private:
	static void OnAttach(Window& window);
	static void OnUpdate(Window& window);
	static void OnEvent(Event event, Window& window);
	static void OnDetach();

	static inline Camera m_Camera;

	static inline Shader m_Shader;
	static inline Model m_Model;
};