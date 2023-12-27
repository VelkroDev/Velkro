#pragma once

#include <spdlog/spdlog.h>

#include "../API.h"

namespace Velkro
{
	class Logger
	{
	public:
		VELKRO_API		static bool Init();
	};
};

/* Engine Logging */
#define VLK_CORE_TRACE(...)	::spdlog::log(spdlog::level::trace,    __VA_ARGS__)
#define VLK_CORE_INFO(...)	::spdlog::log(spdlog::level::info,     __VA_ARGS__)
#define VLK_CORE_WARN(...)	::spdlog::log(spdlog::level::warn,     __VA_ARGS__)
#define VLK_CORE_ERROR(...)	::spdlog::log(spdlog::level::err,      __VA_ARGS__)
#define VLK_CORE_FATAL(...)	::spdlog::log(spdlog::level::critical, __VA_ARGS__)

/* Client Logging */
#define VLK_TRACE(...)	::spdlog::trace(__VA_ARGS__)
#define VLK_INFO(...)	::spdlog::info(__VA_ARGS__)
#define VLK_WARN(...)	::spdlog::warn(__VA_ARGS__)
#define VLK_ERROR(...)	::spdlog::error(__VA_ARGS__)
#define VLK_FATAL(...)	::spdlog::critical(__VA_ARGS__)