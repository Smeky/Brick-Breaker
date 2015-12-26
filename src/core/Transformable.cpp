#include "Transformable.hpp"

#include <cmath>

namespace bb {

Transformable::Transformable()
: m_scale( 1, 1 )
, m_rotation( 0 )
, m_isUpdateMatrix( false )
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

void Transformable::setSize( const Vec2f& size ) {
    m_size = size;

    m_isUpdateMatrix = true;
}

const Matrix4& Transformable::getMatrix() const {
    if( m_isUpdateMatrix ) {
        m_matrix = Matrix4();

        // Position
        m_matrix = translate( m_matrix, m_pos - m_origin );

        // Rotation
        m_matrix = translate( m_matrix, m_origin );
        m_matrix = rotate( m_matrix, m_rotation * ( 3.14159 / 180 ) );
        m_matrix = translate( m_matrix, -m_origin );

        // Size
        m_matrix = scale( m_matrix, m_scale * m_size );

        m_isUpdateMatrix = false;
    }

    return m_matrix;
}

} // namespace bb
