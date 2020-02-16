cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(untitled main.cpp)

add_library(IMSL STATIC )



set(SOURCE_FILES main.cpp)
add_executable(OpenGL ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} -lglfw3 -lglfw3dll)