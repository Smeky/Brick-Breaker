#pragma once

#include <Vector2.hpp>
#include <Matrix3.hpp>

namespace bb {

class Transform {
public:
    Transform();

    void setTranslation( const Vec2f& translation );
    void setScale( const Vec2f& scale );
    void setRotation( float radians );

    void translate( const Vec2f& translation );
    void rescale( const Vec2f& scale );
    void rotate( float radians );

    Matrix3 getMatrix() const;

private:
    Vec2f m_position;
    Vec2f m_scale;
    float m_rotation; // In radians
};

} // namespace bb
