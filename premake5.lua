workspace "Velkro"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Core/vendor/glfw/"

project "Core"
	location "Core"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "vlkpch.h"
	pchsource "vlkpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"		
	}

	includedirs
	{
		"vendor/spdlog/include",
		"%{prj.name}/vendor/glfw/include/"		
	}

	links
	{
		"GLFW"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
   
		defines
		{
			"VLK_PLATFORM_WINDOWS",
			"VLK_EXPORTS"
		}

		postbuildcommands
		{
			("copy /B /Y ..\\bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.dll ..\\bin\\" .. outputdir .. "\\Runtime\\ > nul")
		}

	filter "configurations:Debug"
		defines "VLK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VLK_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "VLK_DISTRIBUTION"
		optimize "On"

project "Runtime"
	location "Runtime"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"		
	}

	includedirs
	{
		"Core/src",
		"vendor/spdlog/include",
		"Core/vendor/glfw/include/"
	}

	links
	{
		"Core"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VLK_PLATFORM_WINDOWS",	
		}

	filter "configurations:Debug"
		defines "VLK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VLK_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "VLK_DISTRIBUTION"
		optimize "On"