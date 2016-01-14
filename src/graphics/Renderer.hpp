#pragma once

#include <stdint-gcc.h>
#include <VertexArray.hpp>
#include <RenderStates.hpp>

namespace bb {

class Shader;
class Drawable;

class Renderer {
public:
    Renderer();

    bool init();
    void close();

    void draw( const Drawable& drawable, const RenderStates& states ) const;
    void draw( const VertexArray& vertices, const RenderStates& states = RenderStates() ) const;

private:
    Shader* m_defShader; // Default shader

    uint32_t m_quadVBO;
    uint32_t m_quadVAO;
    uint32_t m_quadEBO;
};

} // namespace bb
