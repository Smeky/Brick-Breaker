#include "Transformable.hpp"

namespace bb {

Transformable::Transformable()
{}

Transformable::Transformable( float x, float y, float w /* = 0 */, float h /* = 0 */ )
: m_pos( x, y )
, m_size( w, h )
{}

Transformable::Transformable( const Vec2f& pos, const Vec2f& size /* = Vec2f() */ )
: m_pos( pos )
, m_size( size )
{}

void Transformable::setPos( const Vec2f& pos ) {
    m_pos = pos;
}

void Transformable::setPos( float x, float y ) {
    m_pos.x = x;
    m_pos.y = y;
}

void Transformable::setPos( float pos ) {
    m_pos.x = pos;
    m_pos.y = pos;
}

Vec2f Transformable::getPos() const {
    return m_pos;
}

void Transformable::move( const Vec2f& movement ) {
    m_pos += movement;
}

void Transformable::move( float x, float y ) {
    m_pos.x += x;
    m_pos.y += y;
}

void Transformable::move( float movement ) {
    m_pos.x += movement;
    m_pos.y += movement;
}

} // namespace bb
