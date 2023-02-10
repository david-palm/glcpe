#include "OpenGLVertexArray.h"

static GLenum convertShaderDataTypeToGLBaseType(ShaderDataType shaderDataType)
{
    switch(shaderDataType)
    {
        case ShaderDataType::Bool:  return GL_BOOL;
        case ShaderDataType::Int:   return GL_INT;
        case ShaderDataType::Float: return GL_FLOAT;
        case ShaderDataType::Vec2:  return GL_FLOAT;
        case ShaderDataType::Vec4:  return GL_FLOAT;
        case ShaderDataType::Mat4:  return GL_FLOAT;
    }
    std::cerr << "Unknown shader data type!" << std::endl;

    return -1;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_VaoId);

}

void OpenGLVertexArray::bind() const
{
    glBindVertexArray(m_VaoId);
}

void OpenGLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    glBindVertexArray(m_VaoId);
    vertexBuffer->bind();
    uint32_t index = 0;
    BufferLayout bufferLayout = vertexBuffer->getLayout();
    for(const BufferElement& bufferElement: bufferLayout)
    {
        glVertexAttribPointer(index,
                              bufferElement.getComponentCount(),
                              convertShaderDataTypeToGLBaseType(bufferElement.getDataType()),
                              bufferElement.isNormalized() ? GL_TRUE : GL_FALSE,
                              bufferLayout.getStride(),
                              (void *) bufferElement.getOffset());
        glEnableVertexAttribArray(index);
        index++;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_VaoId);
    indexBuffer->bind();
    m_IndexBuffer = indexBuffer;
}

