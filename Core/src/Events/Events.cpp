#include <vlkpch.h>

#include "Events.h"

namespace Velkro
{
	void Event::SetEventCallback(EventCallback eventCallback)
	{
		m_EventCallback = eventCallback;
	}

	void Event::Update(Window& window)
	{
		glfwSetKeyCallback(window.m_Window, KeyCallback);
		glfwSetMouseButtonCallback(window.m_Window, MouseButtonCallback);

		Event event;
		event.m_KeyEvents = m_KeyEvents;
		event.m_MouseButtonEvents = m_MouseButtonEvents;
		m_EventCallback(event);
	}

	VLK_EVENT Event::GetKeyEvent(VLK_KEY_CODE key)
	{
		if (m_KeyEvents.find(key) != m_KeyEvents.end())
		{
			return m_KeyEvents[key];
		}
		else
		{
			return VLK_UNKNOWN_ACTION;
		}
	}

	VLK_EVENT Event::GetMouseButtonEvent(VLK_MOUSE_BUTTON_CODE mouseButton)
	{
		if (m_MouseButtonEvents.find(mouseButton) != m_MouseButtonEvents.end())
		{
			return m_MouseButtonEvents[mouseButton];
		}
		else
		{
			return VLK_UNKNOWN_ACTION;
		}
	}

	void Event::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//TODO: Add repeat detection system.

		if (action == GLFW_REPEAT)
		{
			m_KeyEvents[key] = VLK_PRESS;
		}
		else
		{
			m_KeyEvents[key] = action;
		}
	}

	void Event::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		//TODO: Add repeat detection system.

		if (action == GLFW_REPEAT)
		{
			m_MouseButtonEvents[button] = VLK_PRESS;
		}
		else
		{
			m_MouseButtonEvents[button] = action;
		}
	}
}