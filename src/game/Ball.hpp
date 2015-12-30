#pragma once

#include <CircleShape.hpp>

namespace bb {

class Ball : public CircleShape {
public:
    Ball();

    void setVelocity( float velocity );
    float getVelocity() const;

    void setDirVelocity( const Vec2f& velocity );
    Vec2f getDirVelocity() const;

    void setFired( bool fired );
    bool isFired() const;

private:
    float m_velocity;
    Vec2f m_dirVelocity;

    bool m_isFired;
};

} // namespace bb
