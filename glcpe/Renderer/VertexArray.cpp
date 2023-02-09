#include "VertexArray.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::create()
{
    /*
    switch (Renderer::getCurrentAPI())
    {
        case RendererAPI::OpenGL: return new OpenGLVertexArray();
    }
     */
    return new OpenGLVertexArray();

}
