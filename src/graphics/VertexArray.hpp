#pragma once

#include <vector>
#include <Vertex.hpp>

namespace bb {

struct VertexArray {
public:
    VertexArray();

    Vertex& operator[]( uint32_t index );
    const Vertex& operator[]( uint32_t index ) const;

    void resize( uint32_t size );
    size_t size() const;
    const Vertex* data() const;

    std::vector<Vertex>& getVector();
    const std::vector<Vertex>& getVector() const;

private:
    std::vector<Vertex> m_vertices;

};

} // namespace bb
