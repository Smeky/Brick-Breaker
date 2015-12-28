#include "VertexArray.hpp"

namespace bb {

VertexArray::VertexArray()
: m_primitiveType( PrimitiveType::PType_Triangles )
{}

Vertex& VertexArray::operator[]( uint32_t index ) {
    return m_vertices[ index ];
}

const Vertex& VertexArray::operator[]( uint32_t index ) const {
    return m_vertices[ index ];
}

void VertexArray::resize( uint32_t size ) {
    m_vertices.resize( size );
}

size_t VertexArray::size() const {
    return m_vertices.size();
}

const Vertex* VertexArray::data() const {
    return m_vertices.data();
}

std::vector<Vertex>& VertexArray::getVector() {
    return m_vertices;
}

const std::vector<Vertex>& VertexArray::getVector() const {
    return m_vertices;
}

void VertexArray::setPrimitiveType( PrimitiveType type ) {
    m_primitiveType = type;
}

PrimitiveType VertexArray::getPrimitiveType() const {
    return m_primitiveType;
}

} // namespace bb
