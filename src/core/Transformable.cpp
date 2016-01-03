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

void Transformable::setSize( float w, float h ) {
    setSize( { w, h } );
}

void Transformable::setSize( float wh ) {
    setSize( { wh, wh } );
}

Vec2f Transformable::getSize() const {
    return m_size;
}

void Transformable::resize( const Vec2f& size ) {
    setSize( m_size + size );
}

void Transformable::resize( float w, float h ) {
    setSize( m_size + Vec2f( w, h ) );
}

void Transformable::resize( float wh ) {
    setSize( m_size + Vec2f( wh, wh ) );
}

void Transformable::setCenter( const Vec2f& center ) {
    m_pos = center - m_size / 2;

    m_isUpdateMatrix = true;
}

void Transformable::setCenter( float x, float y ) {
    setCenter( { x, y } );
}

void Transformable::setCenter( float xy ) {
    setCenter( { xy, xy } );
}

Vec2f Transformable::getCenter() const {
    return m_pos + m_size / 2;
}

void Transformable::setBox( const Vec4f& box ) {
    setPos( Vec2f( box.x, box.y ) );
    setSize( Vec2f( box.z, box.w ) );
}

void Transformable::setBox( float x, float y, float w, float h ) {
    setPos( Vec2f( x, y ) );
    setSize( Vec2f( w, h ) );
}

void Transformable::setBox( const Vec2f& pos, const Vec2f& size ) {
    setPos( pos );
    setSize( size );
}

void Transformable::setBox( float xy, float wh ) {
    setPos( Vec2f( xy ) );
    setSize( Vec2f( xy ) );
}

Vec4f Transformable::getBox() const {
    return Vec4f( m_pos, m_size );
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
