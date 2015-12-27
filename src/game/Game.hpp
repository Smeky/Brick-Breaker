#pragma once

#include <SDL2/SDL.h>
#include <Sprite.hpp>
#include <Renderer.hpp>

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

    Sprite m_sprite;
    Sprite m_sprite2;

    Renderer m_renderer;
};

} // namespace bb
