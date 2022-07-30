cmake_minimum_required(VERSION 3.10)

#set the project name and version
project(Agate VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_compile_definitions(Agate_STATIC)

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
        )

include_directories("${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/Agate"
        "${PROJECT_SOURCE_DIR}/vender/glfw/include"
        )

set(dir ${PROJECT_SOURCE_DIR}/bin/-windows-x86_64/Agate)

set(LIBRARY_OUTPUT_PATH  ${dir} CACHE PATH "Build directory" FORCE)

add_subdirectory(vender/glfw)
add_library(Agate-lib STATIC ${libSrc})

