#pragma once

#include <Powerup.hpp>
#include <Timer.hpp>

namespace bb {

struct PowerupEffect {
    Powerup::Type type;
    Timer timer;
    bool active = false;

    bool update( Time delta );
};

} // namespace bb
