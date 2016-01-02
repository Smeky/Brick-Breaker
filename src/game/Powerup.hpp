#pragma once

#include <RectShape.hpp>

namespace bb {

struct Powerup : public RectShape {
    enum Type {
        AddBall,
        Speedup,
        Slow,
        PaddleGrow,
        PaddleShrink,
        Damage,
        Chaos,

        Total // KeepLast
    };

    Type type;
};

} // namespace bb
