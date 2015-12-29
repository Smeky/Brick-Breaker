#pragma once

#include <Keyboard.hpp>

namespace bb {

struct Event {
    enum Type {
        Window,
        Keyboard,
        MouseMove,
        MouseButton,
        MouseWheel,
        Quit,

        KeyPressed,
        KeyReleased,
    };

    Type type;
    Key key;
};

} // namespace bb
