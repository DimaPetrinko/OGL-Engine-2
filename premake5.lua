workspace "OGL-Engine-2"
	language "C++"
	cppdialect "C++17"
	
	configurations {"Debug", "Release"}
	platforms { "Win64", "Linux64" }

	startproject = "TestApplication"

	filter {"platforms:Win64"}
		system "windows"
		architecture "x64"
	filter {"platforms:Linux64"}
		system "linux"
		architecture "x64"

	filter {"configurations:Debug"}
		symbols "On"
	filter {"configurations:Release"}
		optimize "On"
	filter {}

	targetdir ("build/%{cfg.buildcfg}/%{prj.name}/bin")
	objdir ("build/%{cfg.buildcfg}/%{prj.name}/obj")

	project "OGLEngine2"
		location ("../%{wks.name}/%{prj.name}")
		kind "StaticLib"
		files "%{prj.name}/src/**"
		includedirs 
		{
			"%{prj.name}/src/",
			"%{prj.name}/include/"
		}
		libdirs {"%{prj.name}/lib/%{cfg.platform}"}
		filter {"platforms:Win64"}
			defines { "GLEW_STATIC", "PLATFORM_WIN64" }
			links {"glfw3", "glew32s", "opengl32", "Gdi32", "legacy_stdio_definitions"}
		filter {"platforms:Linux64"}
			defines { "PLATFORM_LINUX64" }
			links {"glfw", "GLEW", "GL"}
		filter {}
		--postbuildcommands {"{COPY} copy dll to the TestApplication bin folder"}

	project "TestApplication"
		location ("../%{wks.name}/%{prj.name}")
		kind "ConsoleApp"
		files "%{prj.name}/src/**"
		includedirs
		{
			"%{prj.name}/src/",
			"%{prj.name}/include/"
		}
		filter {"platforms:Win64"}
			defines { "PLATFORM_WIN64" }
		filter {"platforms:Linux64"}
			defines { "PLATFORM_LINUX64" }
		filter {}
		links {"OGLEngine2"}