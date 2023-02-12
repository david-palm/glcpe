#include "VertexArray.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"


VertexArray* VertexArray::create()
{

    switch (Renderer::getAPI())
    {
        case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
    }

    return new OpenGLVertexArray();

}

