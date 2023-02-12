#pragma once

#include <memory>
#include "../Math/Vec4.h"
#include "VertexArray.h"

class RendererAPI {
public:
    enum class API
    {
        OpenGL = 0
    };
public:
    virtual void setClearColor(const Vec4 &color) = 0;
    virtual void clear() = 0;

    virtual void drawIndexed(const std::shared_ptr<VertexArray> & vertexArray) = 0;

    static inline API getAPI()
    {
        return s_API;
    }
private:
    static API s_API;
};