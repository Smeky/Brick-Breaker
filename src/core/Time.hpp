#pragma once

#include <stdint-gcc.h>
#include <ostream>

namespace bb {

struct Time {
    float seconds;

    Time();
    Time( float _seconds );

    void setMilliseconds( uint32_t ms );
    uint32_t asMilliseconds() const;

    bool operator==( Time other ) const;
    bool operator!=( Time other ) const;
    Time operator+( Time other ) const;
    Time operator-( Time other ) const;
    Time& operator+=( Time other );
    Time& operator-=( Time other );

    float operator*( float f ) const;

    static Time fromMilliseconds( uint32_t ms );
};

float operator*( float f, Time t );

std::ostream& operator<<( std::ostream& os, Time time );

} // namespace bb
