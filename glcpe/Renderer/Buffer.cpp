#include "Buffer.h"

#include "../Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
{

    switch (Renderer::getAPI())
    {
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }

    return new OpenGLVertexBuffer(vertices, size);

}

IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
{

    switch (Renderer::getAPI())
    {
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
    }

    return new OpenGLIndexBuffer(indices, count);

}