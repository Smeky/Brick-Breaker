#include "Keyboard.hpp"

#include <SDL2/SDL_events.h>

namespace bb {

namespace Keyboard {

    bool isPressed( Key key ) {
        if( key != Key::Unknown ) {
            SDL_PumpEvents();

            // Key state is 1 if key is pressed, 0 otherwise
            const uint8_t* states = SDL_GetKeyboardState( nullptr );

            return states[ key ];
        }

        return false;
    }

} // namespace Keyboard

} // namespace bb
