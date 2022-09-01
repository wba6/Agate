cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(imgui VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB libSrcImgui
        "imconfig.h"
        "imgui.h"
        "imgui.cpp"
        "imgui_draw.cpp"
        "imgui_internal.h"
        "imgui_tables.cpp"
        "imgui_widgets.cpp"
        "imstb_rectpack.h"
        "imstb_textedit.h"
        "imstb_truetype.h"
        "imgui_demo.cpp"

        )


add_library(imgui STATIC ${libSrcImgui} )
