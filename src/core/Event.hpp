#pragma once

#include <Keyboard.hpp>

namespace bb {

struct Event {
    enum Type {
        Unknown,

        KeyDown,
        KeyUp,

        MouseMotion,
        MouseButtonDown,
        MouseButtonUp,
        MouseWheel,

        Quit,
    };

    union {
        Key key;
    };

    Type type;
};

} // namespace bb
