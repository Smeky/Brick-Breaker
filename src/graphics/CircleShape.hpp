#pragma once

#include <Shape.hpp>

namespace bb {

class CircleShape : public Shape {
public:
    CircleShape();

    void setRadius( float radius );
    float getRadius() const;

    void setPointCount( size_t count );
    size_t getPointCount() const;

private:
    void updatePoints();

private:
    float m_radius;
    size_t m_pointCount;

};

} // namespace bb
