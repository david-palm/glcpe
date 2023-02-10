cmake_minimum_required(VERSION 3.22)
project(glcpe)

set(CMAKE_CXX_STANDARD 20)

add_executable(glcpe
               glcpe/main.cpp
               glcpe/Application.cpp
               glcpe/Application.h
               glcpe/Window.h
               glcpe/Platform/OpenGL/OpenGLBuffer.cpp
               glcpe/Platform/OpenGL/OpenGLBuffer.h
               glcpe/Platform/OpenGL/OpenGLVertexArray.h
               glcpe/Platform/OpenGL/OpenGLVertexArray.cpp
               glcpe/Layer.cpp
               glcpe/Layer.h
               glcpe/LayerStack.cpp
               glcpe/LayerStack.h
               glcpe/Platform/Windows/WindowsWindow.cpp
               glcpe/Platform/Windows/WindowsWindow.h
               glcpe/Events/Event.h
               glcpe/Events/KeyEvent.h
               glcpe/Events/MouseEvent.h
               glcpe/Events/WindowEvent.h
               glcpe/Layer.cpp
               glcpe/Layer.h
               glcpe/LayerStack.cpp
               glcpe/LayerStack.h)

# Adding subdirectory for glcpe
add_subdirectory(glcpe)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(glcpe PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s FULL_ES3=1")
else()
    # Add -mwindows to disable all prints for production build
    target_link_libraries(glcpe -lmingw32 -lSDL2Main -lSDL2)
endif()
# Adding subdirectories for vendor libraries
add_subdirectory(vendor/glad)

# Linking libraries to main glwe project
target_link_libraries(glcpe glad)

# Adding include directories of libraries to main glwe project
target_include_directories(glcpe PUBLIC /vendor/glad/include)