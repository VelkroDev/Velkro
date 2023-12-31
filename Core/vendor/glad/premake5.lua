project "GLAD"
    kind "StaticLib"
    language "C"

	targetdir ("bin/" .. outputdir)
    objdir ("bin-obj/" .. outputdir)

	files
	{
        "include/**.h",
        "src/**.c"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"