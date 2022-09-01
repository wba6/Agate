cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(imgui VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB libSrcimgui
        "**.h"
        "**.cpp"
        )

add_library(imgui STATIC ${libSrcimgui})