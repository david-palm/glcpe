cmake_minimum_required(VERSION 3.22)
project(glcpe)

set(CMAKE_CXX_STANDARD 20)

add_executable(glcpe glcpe/main.cpp)

# Adding subdirectory for glcpe
add_subdirectory(glcpe)

# Adding subdirectories for vendor libraries
add_subdirectory(vendor/glad)

# Linking libraries to main glwe project
target_link_libraries(glcpe glad)
target_link_libraries(glcpe -lmingw32 -lSDL2Main -lSDL2 -mwindows)

# Adding include directories of libraries to main glwe project
target_include_directories(glcpe PUBLIC /vendor/glad/include)