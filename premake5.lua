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
include "Core/vendor/glad/"

project "Core"
	location "Core"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchsource "%{prj.name}/src/PCH/vlkpch.cpp"
	pchheader "vlkpch.h"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"vendor/glm/",
		"vendor/spdlog/include",
		"%{prj.name}/vendor/glfw/include/",
		"%{prj.name}/vendor/glad/include/",
		"%{prj.name}/vendor/stb/include/",
		"%{prj.name}/vendor/json/include/",
		"%{prj.name}/src/PCH/"
	}

	links
	{
		"GLFW",
		"GLAD"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
   
		defines
		{
			"VLK_PLATFORM_WINDOWS",
			"VLK_EXPORTS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Runtime")
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
		"Core/src/PCH",
		"vendor/glm/",
		"vendor/spdlog/include",
		"Core/vendor/glfw/include/",
		"Core/vendor/glad/include/",
		"Core/vendor/stb/include/",
		"Core/vendor/json/include/"
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
			"GLFW_INCLUDE_NONE"
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