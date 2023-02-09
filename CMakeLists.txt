cmake_minimum_required(VERSION 3.22)
project(glcpe)

set(CMAKE_CXX_STANDARD 20)

add_executable(glcpe glcpe/main.cpp glcpe/Application.cpp glcpe/Application.h)

# Adding subdirectory for glcpe
add_subdirectory(glcpe)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(glcpe PROPERTIES LINK_FLAGS "-s USE_SDL=2 -s FULL_ES3=1")
else()
    target_link_libraries(glcpe -lmingw32 -lSDL2Main -lSDL2 -mwindows)
endif()
# Adding subdirectories for vendor libraries
add_subdirectory(vendor/glad)

# Linking libraries to main glwe project
target_link_libraries(glcpe glad)

# Adding include directories of libraries to main glwe project
target_include_directories(glcpe PUBLIC /vendor/glad/include)