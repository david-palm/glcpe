#include "Buffer.h"

#include "../Platform/OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
{
    /*
    switch (Renderer::getCurrentAPI())
    {
        case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }
     */
    return new OpenGLVertexBuffer(vertices, size);

}

IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
{
    /*
    switch (Renderer::getCurrentAPI())
    {
        case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
    }
     */
    return new OpenGLIndexBuffer(indices, count);

}