#include "Player.hpp"

namespace bb {

Player::Player()
: m_velocity( 0 )
{}

void Player::setVelocity( float velocity ) {
    m_velocity = velocity;
}

float Player::getVelocity() const {
    return m_velocity;
}

} // namespace bb
