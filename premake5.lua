workspace "Agate"
	architecture"x64"
	startproject "Application"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.build}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Agate/vender/glfw/include"


include "Agate/vender/glfw"

project "Agate"
	location "Agate"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "agpch.h"
	pchsource "Agate/src/agpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/Agate",
		"%{IncludeDir.GLFW}"
	}

	links{
		"opengl32.lib",
		"GLFW"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"Agate_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Application")
		}
		
	filter "configurations:Debug"
	    defines "AG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
	    defines "AG_Release"
		buildoptions "/MD"
		optimize  "On"

	filter "configurations:Dist"
	    defines "AG_Dist"
		buildoptions "/MD"
		optimize  "On"

project "Application"
	location "Application"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Agate/src",
	}

	links
	{
		"Agate"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		

	filter "configurations:Debug"
	    defines "AG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
	    defines "AG_Release"
		buildoptions "/MD"
		optimize  "On"

	filter "configurations:Dist"
	    defines "AG_Dist"
		buildoptions "/MD"
		optimize  "On"
	
