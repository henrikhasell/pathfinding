cmake_minimum_required(VERSION 3.1)
project("Tower Defence Project" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
file(GLOB SOURCES "main.cpp" "src/*.cpp")
add_executable(game ${SOURCES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
target_link_libraries(game ${OPENGL_LIBRARIES})

find_package(glfw3 REQUIRED)
target_link_libraries(game glfw)
