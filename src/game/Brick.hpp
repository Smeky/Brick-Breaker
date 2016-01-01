#pragma once

#include <RectShape.hpp>

namespace bb {

class Brick : public RectShape {
public:
    Brick();

    // Calculates angles of its corners for faster collision calculation
    void updateCornerAngles();
    const float* getCornerAngles() const;

private:
    float m_cornerAngles[ 4 ];

};

} // namespace bb
