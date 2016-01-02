#include "PowerupEffect.hpp"

namespace bb {

bool PowerupEffect::update( Time delta ) {
    return timer.update( delta );
}

} // namespace bb
