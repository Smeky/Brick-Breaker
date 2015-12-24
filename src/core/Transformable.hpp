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

    const Matrix4& getMatrix();

protected:
    Matrix4 m_matrix;

    Vec2f m_pos;
    Vec2f m_scale;
    Vec2f m_origin;
    float m_rotation;   // In radians

private:
    bool m_isUpdateMatrix;
};

} // namespace bb
