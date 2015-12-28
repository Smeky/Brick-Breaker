#pragma once

#include <stdint-gcc.h>
#include <VertexArray.hpp>

namespace bb {

struct RenderStates;
class Shader;

class Renderer {
public:
    Renderer();

    bool init();
    void close();

    void draw( const VertexArray& vertices, const RenderStates& states ) const;

private:
    Shader* m_defShader; // Default shader

    uint32_t m_vbo;
    uint32_t m_vao;

    const uint32_t m_defMaxVertexCount;
    mutable VertexArray m_vertexCache;
    uint32_t m_maxVertexCount;
};

} // namespace bb