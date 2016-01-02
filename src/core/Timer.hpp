#pragma once

#include <Time.hpp>

namespace bb {

class Timer {
public:
    Timer( Time limit = 0.0, Time current = 0.0 );

    bool update( Time delta );

    void reset();

    void setLimit( Time limit );
    const Time& getLimit() const;

    void setCurrent( Time current );
    const Time& getCurrent() const;

    void setLimitAndCurrent( Time both );

    bool isTime() const;

private:
    Time m_limit;
    Time m_current;
};

} // namespace bb
