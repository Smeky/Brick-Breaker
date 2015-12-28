#include "Time.hpp"

#include <iomanip>

namespace bb {

Time::Time()
: seconds( 0.0 )
{}

Time::Time( float _seconds )
: seconds( _seconds )
{}

void Time::setMilliseconds( uint32_t ms ) {
    seconds = (float)ms / 1000;
}

uint32_t Time::asMilliseconds() const {
    return (uint32_t)( seconds * 1000 );
}

bool Time::operator==( Time other ) const {
    return seconds == other.seconds;
}

bool Time::operator!=( Time other ) const {
    return seconds != other.seconds;
}

Time Time::operator+( Time other ) const {
    return Time( seconds + other.seconds );
}

Time Time::operator-( Time other ) const {
    return Time( seconds - other.seconds );
}

Time& Time::operator+=( Time other ) {
    return ( *this = (*this) + other );
}

Time& Time::operator-=( Time other ) {
    return ( *this = (*this) - other );
}

std::ostream& operator<<( std::ostream& os, Time time ) {
    return os << std::fixed << std::setprecision( 2 ) << time.seconds << "s";
}

} // namespace bb
