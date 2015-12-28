#include "Clock.hpp"

#include <SDL2/SDL_timer.h>

namespace bb {

Clock::Clock()
: m_startTicks( SDL_GetTicks() )
{}

Time Clock::getElapsedTime() const {
    return Time::fromMilliseconds( SDL_GetTicks() - m_startTicks );
}

Time Clock::restart() {
    uint32_t ticks = SDL_GetTicks();
    Time t = Time::fromMilliseconds( ticks - m_startTicks );

    m_startTicks = ticks;

    return t;
}

std::ostream& operator<<( std::ostream& os, const Clock& clock ) {
    return os << clock.getElapsedTime();
}

} // namespace bb
