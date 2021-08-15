workspace "openBully"
	language "C++"
	configurations { "Release", "Debug" }
	location "build"
	symbols "Full"
	
project "openBully"
	kind "SharedLib"
	optimize "Speed"
	targetextension ".asi"
	targetdir "D:/Bully"
	files {"src/**.h", "src/**.cpp"}
	includedirs { "src" }
		includedirs { "src/animation" }
		includedirs { "src/area" }
		includedirs { "src/audio" }
			includedirs { "src/audio/scream" }
		includedirs { "src/camera" }
		includedirs { "src/classes" }
		includedirs { "src/collision" }
		includedirs { "src/control" }
		includedirs { "src/core" }
			includedirs { "src/core/managers" }
		includedirs { "src/custom" }
		includedirs { "src/entities"}
		includedirs { "src/math" }
		includedirs { "src/memory"}
		includedirs { "src/minigames"}
		includedirs { "src/modelinfo"}
		includedirs { "src/objects" }
		includedirs { "src/patch" }
		includedirs { "src/peds" }
		includedirs { "src/pickups" }
		includedirs { "src/render" }
		includedirs { "src/rw" }
		includedirs { "src/scripts" }
		includedirs { "src/vehicles" }
		includedirs { "src/weapons" }