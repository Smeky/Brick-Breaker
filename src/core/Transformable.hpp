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
    void setSize( float w, float h );
    void setSize( float wh );
    Vec2f getSize() const;

    void resize( const Vec2f& size );
    void resize( float w, float h );
    void resize( float wh );

    void setCenter( const Vec2f& center );
    void setCenter( float x, float y );
    void setCenter( float xy );
    Vec2f getCenter() const;

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
