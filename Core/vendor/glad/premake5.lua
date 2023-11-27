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