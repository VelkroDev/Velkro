#pragma once

#include "API.h"

#include "Window/Window.h"

#include "FileManager/FileInput.h"
#include "FileManager/FileOutput.h"

#include "Renderer/Renderer.h"

#include "Camera/Camera.h"

#include "Events/Events.h"

namespace Velkro
{
	class Application
	{
		using AttachCallback = std::function<void(Window& window)>;
		using UpdateCallback = std::function<void(Window& window)>;
		using AppEventCallback = std::function<void(Event& event, Window& window)>;
		using DetachCallback = std::function<void()>;

	public:
		VELKRO_API		Application();
		VELKRO_API		~Application();
		
		VELKRO_API		static void OnEvent(Event& event);

		VELKRO_API		static void SetAttachCallback(AttachCallback attachCallback);
		VELKRO_API		static void SetUpdateCallback(UpdateCallback updateCallback);
		VELKRO_API		static void SetDetachCallback(DetachCallback detachCallback);

		VELKRO_API		static void SetEventCallback(AppEventCallback eventCallback);

		VELKRO_API		void Run();

	private:
		VELKRO_API		static inline AttachCallback m_AttachCallback;
		VELKRO_API		static inline UpdateCallback m_UpdateCallback;
		VELKRO_API		static inline DetachCallback m_DetachCallback;
		
		VELKRO_API		static inline AppEventCallback m_EventCallback;

		VELKRO_API		static inline bool m_Running = true;

		VELKRO_API		static inline Window m_Window;
	};
}