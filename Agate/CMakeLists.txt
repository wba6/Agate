cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(Agate VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB libSrc
        "src/**.h"
        "src/**.cpp"
        "src/Agate/*.h"
        "src/Agate/*.cpp"
        "src/Agate/Math/*.cpp"
        "src/Agate/Math/*.h"
        "src/Agate/Events/*.cpp"
        "src/Agate/Events/*.h"
        "src/Agate/window/*.cpp"
        "src/Agate/window/*.h"
        "vender/glad/src/*.c"
        "src/Agate/imgui-layer/*.cpp"
        "src/Agate/imgui-layer/*.h"
        )

include_directories("${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/Agate"
        "${PROJECT_SOURCE_DIR}/vender/glfw/include"
        "${PROJECT_SOURCE_DIR}/vender/glad/include"
        "${PROJECT_SOURCE_DIR}/vender/spdlog/include"
        "${PROJECT_SOURCE_DIR}/vender/imgui/"
                )


add_subdirectory(vender/glfw)
add_subdirectory(vender/spdlog)
add_subdirectory(vender/imgui)

add_compile_definitions(Agate_STATIC GLFW_INCLUDE_NONE)

add_library(Agate-lib STATIC ${libSrc} src/Agate/imgui-layer/build.cpp src/Agate/renderContext/Context.cpp src/Agate/renderContext/Context.h)

target_precompile_headers(Agate-lib PUBLIC
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/agpch.h>"
        )

