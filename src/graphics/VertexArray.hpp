#pragma once

#include <vector>
#include <Vertex.hpp>

namespace bb {

class VertexArray {
public:
    VertexArray();

    Vertex& operator[]( uint32_t index );
    const Vertex& operator[]( uint32_t index ) const;

    void resize( uint32_t size );
    size_t size() const;
    const Vertex* data() const;

    const std::vector<Vertex>& getVertices() const;

private:
    std::vector<Vertex> m_vertices;

};

} // namespace bb
