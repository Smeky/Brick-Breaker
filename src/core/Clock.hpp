#pragma once

#include <Time.hpp>

namespace bb {

class Clock {
public:
    Clock();

    Time getElapsedTime() const;
    Time restart();

private:
    uint32_t m_startTicks;

};

std::ostream& operator<<( std::ostream& os, const Clock& clock );

} // namespace bb
