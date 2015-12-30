#include "CircleShape.hpp"

#include <cmath>

namespace bb {

CircleShape::CircleShape()
: m_radius( 0.0 )
, m_pointCount( 16 )
{
    // Temporary solution to bug where circle wont display
    // because of 0,0 size
    setSize( 1, 1 );

    m_vertices.setPrimitiveType( PrimitiveType::PType_TriangleFan );
    m_vertices.resize( m_pointCount + 1 );
}

void CircleShape::setRadius( float radius ) {
    m_radius = radius;

    updatePoints();
}

float CircleShape::getRadius() const {
    return m_radius;
}

void CircleShape::setPointCount( size_t count ) {
    m_pointCount = count;

    m_vertices.resize( m_pointCount );

    updatePoints();
}

size_t CircleShape::getPointCount() const {
    return m_pointCount;
}

/* Private */

void CircleShape::updatePoints() {
    for( size_t i = 0; i <= m_pointCount; i++ ) {
        Vertex& vertex = m_vertices[ i ];

        const float angle = i * 2 * 3.1415926535897 / m_pointCount;

        vertex.pos.x = m_radius + m_radius * std::cos( angle );
        vertex.pos.y = m_radius + m_radius * std::sin( angle );
    }
}

} // namespace bb
