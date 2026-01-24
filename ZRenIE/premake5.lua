workspace "ZRenIE"
    architecture "x86_64" -- x64
    configurations {"Debug", "Release"}


include "vendor/glfwPremake" -- Almost like a C++ include where the content of that premake file is pasted in this one
-- include "vendor/assimpPremake" -- For later usage


project "ZRenIE"
    location "ZRenIE"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    
    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "vendor/glad/src/glad.c",

        -- ImGui core
        "vendor/imguiPremake/*.cpp",

        -- ImGui backends (GLFW + OpenGL3)
        "vendor/imguiPremake/backends/imgui_impl_glfw.cpp",
        "vendor/imguiPremake/backends/imgui_impl_opengl3.cpp"
    }

    includedirs
    {
        "vendor/glfwPremake/include",
        "vendor/glad/include",
        "vendor/stb_image",
        "vendor/glm",
        
        -- ASSIMP
        "vendor/assimpPremake/include",
        "vendor/assimpPremake/build/include", -- where CMake generates config.h

        -- ImGUI
        "vendor/imguiPremake",
        "vendor/imguiPremake/backends",

        -- nlohmann
        "vendor/nlohmann",

        -- imfilebrowser
        "vendor/imfilebrowser"
    }
    
    links
    {
        "opengl32.lib",
        "glfwPremake",
    }

    filter "system:windows"
        systemversion "latest" -- Use latest Windows SKDs
        staticruntime "On"

    filter "configurations:Debug"
        defines {"ZR_DEBUG"}
        symbols "On" -- Better debug information

        libdirs { "vendor/assimpPremake/build/lib/Debug" }
        links { "assimpPremake" }

        postbuildcommands
        {
            '{COPY} "%{wks.location}/vendor/assimpPremake/build/bin/Debug/*.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        defines {"ZR_NDEBUG"}
        optimize "On"

        libdirs { "vendor/assimpPremake/build/lib/Release" }
        links { "assimpPremake" }

        postbuildcommands
        {
            '{COPY} "%{wks.location}/vendor/assimpPremake/build/bin/Release/*.dll" "%{cfg.targetdir}"'
        }
