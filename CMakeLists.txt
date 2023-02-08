cmake_minimum_required(VERSION 3.22)
project(glcpe)

set(CMAKE_CXX_STANDARD 20)

add_executable(glcpe glcpe/main.cpp)

target_link_libraries(glcpe -lmingw32 -lSDL2Main -lSDL2 -mwindows)