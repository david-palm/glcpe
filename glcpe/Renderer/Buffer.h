#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

enum class ShaderDataType: uint8_t
{
    Bool, Int, Float, Vec2, Vec4, Mat4
};

static uint32_t sizeOfShaderDataType(ShaderDataType dataType)
{
    switch(dataType)
    {
        case ShaderDataType::Bool:  return 1;
        case ShaderDataType::Int:   return 4;
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Vec2:  return 8;
        case ShaderDataType::Vec4:  return 16;
        case ShaderDataType::Mat4:  return 64;
    }
    std::cerr << "Unknown shader data type!" << std::endl;

    return -1;

}
class BufferElement
{
public:
    BufferElement() { }
    BufferElement(ShaderDataType dataType, const std::string& name, bool normalized = false)
            : m_DataType(dataType), m_Name(name), m_Size(sizeOfShaderDataType(dataType)), m_Offset(0), m_Normalized(false)
    {

    }
    const uint32_t getComponentCount() const
    {
        switch (m_DataType)
        {
            case ShaderDataType::Bool:  return 1;
            case ShaderDataType::Int:   return 1;
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Vec2:  return 2;
            case ShaderDataType::Vec4:  return 4;
            case ShaderDataType::Mat4:  return 16;
        }
        std::cerr << "Unknown shader data type!" << std::endl;

        return -1;
    }
    inline const ShaderDataType getDataType() const{ return m_DataType; }
    inline const std::string getName() const { return m_Name; }
    inline const uint32_t getSize() const { return m_Size; }
    inline const uint32_t getOffset() const { return m_Offset; }
    inline const bool isNormalized() const { return m_Normalized; }

    inline const void setOffset(uint32_t offset) { m_Offset = offset; }

private:
    ShaderDataType m_DataType;
    std::string m_Name;
    uint32_t m_Size;
    uint32_t m_Offset;
    bool m_Normalized;


};

class BufferLayout
{
public:
    BufferLayout() { }
    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_Elements(elements)
        {
            calculateOffsetAndStride();
        }
    inline const std::vector<BufferElement>& getElements() const { return m_Elements; }
    inline const uint32_t getStride() const { return m_Stride; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
private:
    void calculateOffsetAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for(auto& element : m_Elements)
        {
            element.setOffset(offset);
            offset += element.getSize();
            m_Stride += element.getSize();
        }
    }
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride = 0;
};

class VertexBuffer
{
public:
    virtual ~VertexBuffer() {}

    virtual void bind() const= 0;
    virtual void unbind() const = 0;

    virtual const BufferLayout& getLayout() const = 0;
    virtual void setLayout(const BufferLayout& bufferLayout) = 0;

    static VertexBuffer* create(float* vertices, uint32_t size);

};

class IndexBuffer {
public:
    virtual ~IndexBuffer() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual uint32_t getCount() const = 0;
    static IndexBuffer* create(uint32_t* indices, uint32_t count);
};


