#pragma once

#include "API.h"

#include <memory>
#include <functional>
#include <iostream>

#include "Time/Time.h"

namespace Velkro
{
	class Application
	{
		using AttachCallback = std::function<void()>;
		using UpdateCallback = std::function<void()>;
		using DetachCallback = std::function<void()>;

	public:
		VELKRO_API		Application();
		VELKRO_API		~Application();
		
		VELKRO_API		static void SetAttachCallback(AttachCallback attachCallback);
		VELKRO_API		static void SetUpdateCallback(UpdateCallback updateCallback);
		VELKRO_API		static void SetDetachCallback(DetachCallback detachCallback);

		VELKRO_API		void Run();

	private:
		VELKRO_API		static inline AttachCallback m_AttachCallback;
		VELKRO_API		static inline UpdateCallback m_UpdateCallback;
		VELKRO_API		static inline DetachCallback m_DetachCallback;

		VELKRO_API		static inline bool m_Running = true;
	};
}