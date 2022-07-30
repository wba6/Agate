cmake_minimum_required(VERSION 3.10)

#set the project name and version
project(Application VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB appSrc
        "src/*.h"
        "src/*.cpp"
        )

include_directories("../Agate/src")

add_compile_definitions(Agate_STATIC)

set(dir ${PROJECT_SOURCE_DIR}/bin/-windows-x86_64/Application)

set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

add_executable(Application ${appSrc})

target_link_libraries(Application PRIVATE Agate-lib glfw)

