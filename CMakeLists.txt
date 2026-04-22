cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(Agate VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# helps IDE's find files
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(buildDirExecutable ${PROJECT_SOURCE_DIR}/bin/Application/Static)

set(EXECUTABLE_OUTPUT_PATH ${buildDirExecutable} CACHE PATH "Build directory" FORCE)

set(buildDirLib ${PROJECT_SOURCE_DIR}/bin/Agate/Static)

set(LIBRARY_OUTPUT_PATH  ${buildDirLib} CACHE PATH "Build directory" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/Agate)
add_subdirectory(${PROJECT_SOURCE_DIR}/Application)
add_subdirectory(${PROJECT_SOURCE_DIR}/Editor)

# Add a custom target to run the Application executable
add_custom_target(run
    COMMAND $<TARGET_FILE:Application>
    DEPENDS Application
    WORKING_DIRECTORY ${buildDirExecutable}
    COMMENT "Running the Application executable"
)

add_custom_target(run_editor
    COMMAND $<TARGET_FILE:Agate-Editor>
    DEPENDS Agate-Editor
    WORKING_DIRECTORY ${buildDirExecutable}
    COMMENT "Running the Editor executable"
)

add_custom_target(editor
    COMMAND $<TARGET_FILE:Agate-Editor>
    DEPENDS Agate-Editor
    WORKING_DIRECTORY ${buildDirExecutable}
    COMMENT "Building and running the Editor"
)

add_custom_target(debug_editor
    COMMAND gdb $<TARGET_FILE:Agate-Editor>
    DEPENDS Agate-Editor
    WORKING_DIRECTORY ${buildDirExecutable}
    COMMENT "Debugging the Editor executable with GDB"
)
