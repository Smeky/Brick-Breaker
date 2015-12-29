#pragma once

#include <SDL2/SDL.h>
#include <RectShape.hpp>
#include <Renderer.hpp>
#include <Clock.hpp>

namespace bb {

class IGameState;

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

    RectShape m_s1;
    RectShape m_s2;

    Renderer m_renderer;

    Clock m_runClock;

    IGameState* m_gameState;
};

} // namespace bb
