#pragma once

#include <Matrix4.hpp>
#include <Vector2.hpp>

namespace bb {

class Transformable {
public:
    Transformable();

    void setPos( const Vec2f& pos );
    void setPos( float x, float y );
    void setPos( float pos );
    Vec2f getPos() const;

    void move( const Vec2f& movement );
    void move( float x, float y );
    void move( float movement );

    void setOrigin( const Vec2f& origin ) { m_origin = origin; m_isUpdateMatrix = true; }

    void setSize( const Vec2f& size );

    void setRotation( float degrees ) { m_rotation = degrees; m_isUpdateMatrix = true; }

    const Matrix4& getMatrix() const;

protected:
    mutable Matrix4 m_matrix;

    Vec2f m_pos;
    Vec2f m_size;
    Vec2f m_scale;
    Vec2f m_origin;
    float m_rotation;   // In degrees

private:
    mutable bool m_isUpdateMatrix;

};

} // namespace bb
