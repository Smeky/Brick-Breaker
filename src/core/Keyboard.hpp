#pragma once

/**
    Key enumeration does NOT support all keys in SDL
    event scanner yet. There is support only for
    most commonly used keys.
*/

#include <SDL2/SDL_keyboard.h>

namespace bb {

enum Key {
    Unknown = -1,

    Key_0 = SDL_SCANCODE_0,
    Key_1 = SDL_SCANCODE_1,
    Key_2 = SDL_SCANCODE_2,
    Key_3 = SDL_SCANCODE_3,
    Key_4 = SDL_SCANCODE_4,
    Key_5 = SDL_SCANCODE_5,
    Key_6 = SDL_SCANCODE_6,
    Key_7 = SDL_SCANCODE_7,
    Key_8 = SDL_SCANCODE_8,
    Key_9 = SDL_SCANCODE_9,

    Num_0 = SDL_SCANCODE_KP_0,
    Num_1 = SDL_SCANCODE_KP_1,
    Num_2 = SDL_SCANCODE_KP_2,
    Num_3 = SDL_SCANCODE_KP_3,
    Num_4 = SDL_SCANCODE_KP_4,
    Num_5 = SDL_SCANCODE_KP_5,
    Num_6 = SDL_SCANCODE_KP_6,
    Num_7 = SDL_SCANCODE_KP_7,
    Num_8 = SDL_SCANCODE_KP_8,
    Num_9 = SDL_SCANCODE_KP_9,

    A = SDL_SCANCODE_A,
    B = SDL_SCANCODE_B,
    C = SDL_SCANCODE_C,
    D = SDL_SCANCODE_D,
    E = SDL_SCANCODE_E,
    F = SDL_SCANCODE_F,
    G = SDL_SCANCODE_G,
    H = SDL_SCANCODE_H,
    I = SDL_SCANCODE_I,
    J = SDL_SCANCODE_J,
    K = SDL_SCANCODE_K,
    L = SDL_SCANCODE_L,
    M = SDL_SCANCODE_M,
    N = SDL_SCANCODE_N,
    O = SDL_SCANCODE_O,
    P = SDL_SCANCODE_P,
    Q = SDL_SCANCODE_Q,
    R = SDL_SCANCODE_R,
    S = SDL_SCANCODE_S,
    T = SDL_SCANCODE_T,
    U = SDL_SCANCODE_U,
    V = SDL_SCANCODE_V,
    W = SDL_SCANCODE_W,
    X = SDL_SCANCODE_X,
    Y = SDL_SCANCODE_Y,
    Z = SDL_SCANCODE_Z,

    F1 = SDL_SCANCODE_F1,
    F2 = SDL_SCANCODE_F2,
    F3 = SDL_SCANCODE_F3,
    F4 = SDL_SCANCODE_F4,
    F5 = SDL_SCANCODE_F5,
    F6 = SDL_SCANCODE_F6,
    F7 = SDL_SCANCODE_F7,
    F8 = SDL_SCANCODE_F8,
    F9 = SDL_SCANCODE_F9,
    F10 = SDL_SCANCODE_F10,
    F11 = SDL_SCANCODE_F11,
    F12 = SDL_SCANCODE_F12,

    Left = SDL_SCANCODE_LEFT,
    Right = SDL_SCANCODE_RIGHT,
    Down = SDL_SCANCODE_DOWN,
    Up = SDL_SCANCODE_UP,

    Escape = SDL_SCANCODE_ESCAPE,
    Space = SDL_SCANCODE_SPACE,
    CapsLock = SDL_SCANCODE_CAPSLOCK,
    Tab = SDL_SCANCODE_TAB,

    LCtrl = SDL_SCANCODE_LCTRL,
    RCtrl = SDL_SCANCODE_RCTRL,
    LShit = SDL_SCANCODE_LSHIFT,
    RShift = SDL_SCANCODE_RSHIFT,
    LAlt = SDL_SCANCODE_LALT,
    RAlt = SDL_SCANCODE_RALT,
    LGUI = SDL_SCANCODE_LGUI,
    RGUI = SDL_SCANCODE_RGUI,

    Numlock = SDL_SCANCODE_NUMLOCKCLEAR,
};

namespace Keyboard {

bool isPressed( Key key );

} // namespace Keyboard

} // namespace bb
