cmake_minimum_required(VERSION 3.10)

#set the project name and version
project(Agate VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(${PROJECT_SOURCE_DIR}/Agate)



file(GLOB appSrc
        "Application/src/*.h"
        "Application/src/*.cpp"
        )

include_directories("Agate/src")

add_compile_definitions(Agate_STATIC)

add_executable(Agate ${appSrc})

target_link_libraries(Agate PRIVATE Agate-lib glfw)