#include "OpenGLBuffer.h"

//-----------------------------------------------------------------------------
//-----------------------------VertexBuffer------------------------------------
//-----------------------------------------------------------------------------

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
{
    glGenBuffers(1, &m_VboId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_VboId);
}

void OpenGLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
}

void OpenGLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//----------------------------------------------------------------------------
//-----------------------------IndexBuffer------------------------------------
//----------------------------------------------------------------------------

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    : m_Count(count)
{
    glGenBuffers(1, &m_EboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_EboId);
}

void OpenGLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EboId);
}

void OpenGLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}