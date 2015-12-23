#pragma once

#include <Vector2.hpp>

namespace bb {

class Transformable {
public:
    Transformable();
    Transformable( float x, float y, float w = 0, float h = 0 );
    Transformable( const Vec2f& pos, const Vec2f& size = Vec2f() );

    void setPos( const Vec2f& pos );
    void setPos( float x, float y );
    void setPos( float pos );
    Vec2f getPos() const;

    void move( const Vec2f& movement );
    void move( float x, float y );
    void move( float movement );

protected:
    Vec2f m_pos;
    Vec2f m_size;
};

} // namespace bb
