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

    void close();

private:
    void onClose();

    void handleInput();
    void update();
    void render();

private:
    SDL_Window* m_window;
    bool m_running;

    RectShape m_s1;
    RectShape m_s2;

    Renderer m_renderer;

    Clock m_runClock;

    IGameState* m_gameState;
};

} // namespace bb
