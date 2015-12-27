#pragma once

#include <stdint-gcc.h>
#include <VertexArray.hpp>


#include <Shader.hpp>
#include <Matrix4.hpp>

namespace bb {

struct RenderStates {
    Shader* shader = nullptr;
    Matrix4 transform;
};

class Renderer {
public:
    Renderer();

    bool init();
    void close();

    void render( const VertexArray& vertices, const RenderStates& states ) const;

//    static uint32_t createVAO( uint32_t size, const Vertex* vertices );

private:
    Shader* m_defShader; // Default shader

    uint32_t m_vbo;
    uint32_t m_vao;

    const uint32_t m_defMaxVertexCount;
    mutable VertexArray m_vertexCache;
    uint32_t m_maxVertexCount;
};

} // namespace bb
