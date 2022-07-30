cmake_minimum_required(VERSION 3.10)

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
        )

include_directories("${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_SOURCE_DIR}/src/Agate"
        "${PROJECT_SOURCE_DIR}/vender/glfw/include"
        "${PROJECT_SOURCE_DIR}/vender/glad/include"
                )


add_subdirectory(vender/glfw)

add_compile_definitions(Agate_STATIC GLFW_INCLUDE_NONE)

add_library(Agate-lib STATIC ${libSrc})

