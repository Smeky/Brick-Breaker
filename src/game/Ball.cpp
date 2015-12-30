#include "Ball.hpp"

namespace bb {

Ball::Ball()
: m_velocity( 0.0 )
, m_isFired( false )
{}

void Ball::setVelocity( float velocity ) {
    m_velocity = velocity;
}

float Ball::getVelocity() const {
    return m_velocity;
}

void Ball::setDirVelocity( const Vec2f& velocity ) {
    m_dirVelocity = velocity;
}

Vec2f Ball::getDirVelocity() const {
    return m_dirVelocity;
}

void Ball::setFired( bool fired ) {
    m_isFired = fired;
}

bool Ball::isFired() const {
    return m_isFired;
}

} // namespace bb
