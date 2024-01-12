cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(Agate-lib VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
file(GLOB_RECURSE libSrc
        ${PROJECT_SOURCE_DIR}/src/*.c
        ${PROJECT_SOURCE_DIR}/vender/glad/src/*.c
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        )

# Add source header files
file(GLOB_RECURSE libHead
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/*.hpp
        )

include_directories("${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/Agate"
        "${PROJECT_SOURCE_DIR}/src/Agate/Events"
        "${PROJECT_SOURCE_DIR}/vender/glfw/include"
        "${PROJECT_SOURCE_DIR}/vender/glad/include"
        "${PROJECT_SOURCE_DIR}/vender/spdlog/include"
        "${PROJECT_SOURCE_DIR}/vender/imgui/"
        "${PROJECT_SOURCE_DIR}/vender/glm/glm"
        "${PROJECT_SOURCE_DIR}/vender/glm/"
        )


add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/spdlog)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/imgui)
add_subdirectory(${PROJECT_SOURCE_DIR}/vender/glm)

add_compile_definitions(Agate_STATIC GLFW_INCLUDE_NONE)

add_library(Agate-lib STATIC ${libSrc} ${libHead} src/Agate/ImGui-layer/imgui_interface.cpp src/Agate/ImGui-layer/imgui_interface.h src/Agate/Core/keyCodes.h src/Agate/Core/InputPulling.cpp src/Agate/Core/InputPulling.h
        src/Agate/Rendering/OpenGl/VertexLayout.h)

target_precompile_headers(Agate-lib PUBLIC
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/agpch.h>"
        )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/src/Agate/Rendering/Shaders ${buildDirExecutable}/Shaders
        )
