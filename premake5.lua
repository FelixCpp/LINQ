workspace "LINQ-Workspace"
    configurations { "Debug", "Release" }
    architecture "x86_64"
    flags { "MultiProcessorCompile" }

project "LINQ"
    location "LINQ"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/%{cfg.buildcfg}"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"