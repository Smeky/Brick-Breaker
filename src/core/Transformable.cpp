#include "Transformable.hpp"

#include <cmath>

namespace bb {

Transformable::Transformable()
: m_scale( 1, 1 )
, m_rotation( 0 )
, m_isUpdateMatrix( true )
{}

void Transformable::setPos( const Vec2f& pos ) {
    m_pos = pos;

    m_isUpdateMatrix = true;
}

void Transformable::setPos( float x, float y ) {
    setPos( { x, y } );
}

void Transformable::setPos( float pos ) {
    setPos( { pos, pos } );
}

Vec2f Transformable::getPos() const {
    return m_pos;
}

void Transformable::move( const Vec2f& movement ) {
    setPos( m_pos + movement );
}

void Transformable::move( float x, float y ) {
    setPos( m_pos + Vec2f( x, y ) );
}

void Transformable::move( float movement ) {
    setPos( m_pos + Vec2f( movement, movement ) );
}

const Matrix4& Transformable::getMatrix() {
    if( m_isUpdateMatrix ) {
        const float c     = std::cos( m_rotation );
        const float s     = std::sin( m_rotation );
        const float sxc   = m_scale.x * c;
        const float syc   = m_scale.y * c;
        const float sxs   = m_scale.x * s;
        const float sys   = m_scale.y * s;
        const float tx    = -m_origin.x * sxc - m_origin.y * sys + m_pos.x;
        const float ty    = +m_origin.x * sxs - m_origin.y * syc + m_pos.y;

        m_matrix[ 0 ][ 0 ] = sxc;
        m_matrix[ 0 ][ 1 ] = -sys;
        m_matrix[ 0 ][ 3 ] = tx;

        m_matrix[ 1 ][ 0 ] = sxs;
        m_matrix[ 1 ][ 1 ] = syc;
        m_matrix[ 1 ][ 3 ] = ty;

        m_isUpdateMatrix = false;
    }

    return m_matrix;
}

} // namespace bb
