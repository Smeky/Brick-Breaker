#pragma once

#include <SDL.h>
#include <Renderer.hpp>
#include <Clock.hpp>
#include <Timer.hpp>

namespace bb {

class IGameState;

class Game {
public:
    Game();

    bool init();
    void run();

    void close();

    Vec2i getWindowSize() const;

private:
    void onClose();

    void handleInput();
    void update();
    void render();

private:
    SDL_Window* m_window;
    bool m_running;

    Renderer m_renderer;

    Clock m_runClock;

    Timer m_secondsTimer;
    uint32_t m_frameCounter;

    float m_timeAccumulator;

    IGameState* m_gameState;
};

} // namespace bb
