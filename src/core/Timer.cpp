#include "Timer.hpp"

namespace bb {

Timer::Timer( Time limit /* = 0.0 */, Time current /* = 0.0 */ )
: m_limit( limit )
, m_current( current )
{}

bool Timer::update( Time delta ) {
    m_current += delta;

    if( isTime() ) {
        m_current = m_limit;

        return true;
    }
    else {
        return false;
    }
}

void Timer::reset() {
    m_current = 0.0;
}

void Timer::setLimit( Time limit ) {
    m_limit = limit;
}

const Time& Timer::getLimit() const {
    return m_limit;
}

void Timer::setCurrent( Time current ) {
    m_current = current;
}

const Time& Timer::getCurrent() const {
    return m_current;
}

void Timer::setLimitAndCurrent( Time both ) {
    m_limit = both;
    m_current = both;
}

bool Timer::isTime() const {
    return m_current >= m_limit;
}

} // namespace bb
