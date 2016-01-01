#include "Brick.hpp"

namespace bb {

Brick::Brick()
{}

void Brick::updateCornerAngles() {
    Vec2f center = m_size / 2;

    m_cornerAngles[ 0 ] = angle( center, Vec2f() );
    m_cornerAngles[ 1 ] = angle( center, Vec2f( m_size.x, 0 ) );
    m_cornerAngles[ 2 ] = angle( center, m_size );
    m_cornerAngles[ 3 ] = angle( center, Vec2f( 0, m_size.y ) );
}

const float* Brick::getCornerAngles() const {
    return m_cornerAngles;
}

} // namespace bb
