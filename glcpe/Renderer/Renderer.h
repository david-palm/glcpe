#pragma once

#include "RenderCommand.h"
class Renderer
{
public:
    inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
};
