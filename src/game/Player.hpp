#pragma once

#include <RectShape.hpp>

namespace bb {

class Player : public RectShape {
public:
    Player();

    void setVelocity( float velocity );
    float getVelocity() const;

private:
    float m_velocity;
};

} // namespace bb
