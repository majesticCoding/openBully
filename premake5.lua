workspace "openBully"
	language "C++"
	configurations { "Debug", "Release" }
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
    includedirs { "src/core" }
    includedirs { "src/math" }
	includedirs { "src/objects" }
    includedirs { "src/peds" }
    includedirs { "src/pickups" }
    includedirs { "src/render" }
    includedirs { "src/scripts" }