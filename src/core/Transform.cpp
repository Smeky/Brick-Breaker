#include "Transform.hpp"

#include <Vector4.hpp>

namespace bb {

Transform::Transform()
: m_scale( { 1, 1 } )
, m_rotation( 0 )
{}

void Transform::setTranslation( const Vec2f& translation ) {
    m_position = translation;
}

void Transform::setScale( const Vec2f& scale ) {
    m_scale = scale;
}

void Transform::setRotation( float radians ) {
    m_rotation = radians;
}

void Transform::translate( const Vec2f& translation ) {
    m_position += translation;
}

void Transform::rescale( const Vec2f& scale ) {
    m_scale += scale;
}

void Transform::rotate( float radians ) {
    m_rotation += radians;
}

Matrix3 Transform::getMatrix() const {
    return Matrix3();
}

} // namespace bb
