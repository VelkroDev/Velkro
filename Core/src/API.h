#pragma once

#ifndef VLK_PLATFORM_WINDOWS
	#error "Velkro only supports windows currently! Sorry."
#endif

#ifdef VLK_EXPORTS
	#define VELKRO_API _declspec(dllexport)
#else
	#define VELKRO_API _declspec(dllimport)
#endif