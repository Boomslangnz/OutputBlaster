workspace "OutputBlaster"
	configurations { "Debug", "Release" }
	platforms { "x64", "x86" }

	flags { "StaticRuntime", "No64BitChecks" }

	systemversion "10.0.17134.0"

	symbols "On"

	characterset "Unicode"

	flags { "NoIncrementalLink", "NoEditAndContinue", "NoMinimalRebuild" }

	includedirs { "Common Files/", "Game Files/", "Output Files/" }

	libdirs { "" }

	buildoptions { "/MP", "/std:c++17" }

	configuration "Debug*"
		targetdir "build/bin/debug"
		defines "NDEBUG"
		objdir "build/obj/debug"

	configuration "Release*"
		targetdir "build/bin/release"
		defines "NDEBUG"
		optimize "speed"
		objdir "build/obj/release"

	filter "platforms:x86"
		architecture "x32"

	filter "platforms:x64"
		architecture "x64"

project "OutputBlaster"
	targetname "OutputBlaster"
	language "c++"
	kind "StaticLib"

	files
	{
		"**.txt", "**.cpp", "**.h", "Common Files/**.cpp", "Common Files/**.h", "Game Files/**.cpp", "Game Files/**.h", "Output Files/**.cpp", "Output Files/**.h",
	}


