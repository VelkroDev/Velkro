#include "Application.h"

namespace Velkro
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_AttachCallback();

		while (m_Running)
		{
			m_UpdateCallback();	
		}

		m_DetachCallback();	
	}	

	/* CALLBACKS */
	void Application::SetAttachCallback(AttachCallback attachCallback)
	{
		m_AttachCallback = attachCallback;
	}
	void Application::SetUpdateCallback(UpdateCallback updateCallback)
	{
		m_UpdateCallback = updateCallback;
	}
	void Application::SetDetachCallback(DetachCallback detachCallback)
	{
		m_DetachCallback = detachCallback;
	}	
}