#pragma once

#include <SDL2/SDL.h>

namespace bb {

class Game {
public:
    Game();

    bool init();
    void run();

    static void close();

private:
    void onClose();

    void handleInput();
    void update();
    void render();

private:
    static SDL_Window* m_window;
    static bool m_running;

};

} // namespace bb
