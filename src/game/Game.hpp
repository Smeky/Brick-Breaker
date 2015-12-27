#pragma once

#include <SDL2/SDL.h>
#include <Shader.hpp>
#include <Sprite.hpp>

namespace bb {

class Game {
public:
    Game();

    bool init();
    void run();

    static void close();

    static Shader* shader;

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

};

} // namespace bb
