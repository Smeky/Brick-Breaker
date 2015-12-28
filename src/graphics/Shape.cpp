#include "Shape.hpp"

namespace bb {

Shape::Shape()
{}

void Shape::draw( Renderer& renderer, RenderStates states ) const {
    states.transform *= getMatrix();

    renderer.draw( m_vertices, states );
}

} // namespace bb
