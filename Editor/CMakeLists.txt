cmake_minimum_required(VERSION 3.16)
project(Editor VERSION 1.0)

file(GLOB editorSrc
        "src/*.h"
        "src/*.cpp"
        )

include_directories("../Agate/src"
                    "../Agate/src/Agate"
                    "../Agate/src/Agate/Events"
                    "../Agate/src/Agate/Rendering"
                    "../Agate/vender/imgui"
                    "../Agate/vender/glm")

add_compile_definitions(Agate_STATIC)

add_executable(Agate-Editor ${editorSrc})

target_link_libraries(Agate-Editor PRIVATE Agate-lib)
