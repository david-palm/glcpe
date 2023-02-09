cmake_minimum_required(VERSION 3.22)

add_library(Platform_OpenGL OpenGLBuffer.h)
target_link_libraries(Platform_OpenGL Renderer)
target_include_directories(Platform_OpenGL PUBLIC /glwe/Platform/OpenGL)