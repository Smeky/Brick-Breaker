#pragma once

#include <vector>
#include <Vertex.hpp>
#include <PrimitiveTypes.h>

namespace bb {

class VertexArray {
public:
    VertexArray();
    VertexArray( PrimitiveType type, uint32_t size = 0 );

    Vertex& operator[]( uint32_t index );
    const Vertex& operator[]( uint32_t index ) const;

    void resize( uint32_t size );
    size_t size() const;
    const Vertex* data() const;

    std::vector<Vertex>& getVector();
    const std::vector<Vertex>& getVector() const;

    void setPrimitiveType( PrimitiveType type );
    PrimitiveType getPrimitiveType() const;

private:
    std::vector<Vertex> m_vertices;
    PrimitiveType m_primitiveType;
};

} // namespace bb
