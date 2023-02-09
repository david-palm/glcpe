cmake_minimum_required(VERSION 3.22)

add_subdirectory(Math)
add_subdirectory(Renderer)
#add_subdirectory(Platform/OpenGL)

target_link_libraries(glcpe)