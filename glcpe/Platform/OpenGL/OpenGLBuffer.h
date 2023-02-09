#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GLFW_INCLUDE_ES3
#include "GLFW/glfw3.h"
#else
#include "glad/glad.h"
#endif

#include "../../Renderer/Buffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual const BufferLayout& getLayout() const override { return m_Layout; }
    virtual void setLayout(const BufferLayout& bufferLayout) override{ m_Layout = bufferLayout; }
private:
    uint32_t m_VboId;
    BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~OpenGLIndexBuffer();
    virtual void bind() const override;
    virtual void unbind() const override;
    virtual uint32_t getCount() const override { return m_Count; }
private:
    uint32_t m_EboId;
    uint32_t m_Count;
};