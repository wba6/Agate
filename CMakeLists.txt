cmake_minimum_required(VERSION 3.16)

#set the project name and version
project(Agate VERSION 1.0)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(buildDirExecutable ${PROJECT_SOURCE_DIR}/bin/-windows-x86_64/Application/Static)

set(EXECUTABLE_OUTPUT_PATH ${buildDirExecutable} CACHE PATH "Build directory" FORCE)

set(buildDirLib ${PROJECT_SOURCE_DIR}/bin/-windows-x86_64/Agate/Static)

set(LIBRARY_OUTPUT_PATH  ${buildDirLib} CACHE PATH "Build directory" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/Agate)
add_subdirectory(${PROJECT_SOURCE_DIR}/Application)




