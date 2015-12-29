#include "Shape.hpp"

namespace bb {

Shape::Shape()
{}

void Shape::draw( const Renderer& renderer, RenderStates states ) const {
    states.transform *= getMatrix();

    renderer.draw( m_vertices, states );
}

void Shape::setColor( const Color& color ) {
    m_color = color;

    for( Vertex& v : m_vertices.getVector() ) {
        v.color = color;
    }
}

const Color& Shape::getColor() const {
    return m_color;
}

VertexArray& Shape::getVertices() {
    return m_vertices;
}

} // namespace bb
