#pragma once

enum class RendererAPI
{
    OpenGL = 0
};

class Renderer
{
public:
    inline static RendererAPI getCurrentAPI() { return s_RendererAPI; }
    inline static void setCurrentAPI(RendererAPI rendererAPI) { s_RendererAPI = rendererAPI; }
private:
    static RendererAPI s_RendererAPI;
};
