#pragma once

#include <IGameState.hpp>
#include <Game.hpp>
#include <Player.hpp>
#include <Brick.hpp>
#include <Ball.hpp>

#include <vector>

namespace bb {

class LevelState : public IGameState {
public:
    LevelState( Game& game );

    void init();
    void close();

    void handleInput( SDL_Event event );
    void update( Time delta );
    void render( Renderer& renderer, RenderStates states ) const;

private:
    void setupPlayer();
    void setupBricks();

    void givePlayerNewBall();
    void firePlayerBall();

    void handlePlayerMovement( Time delta );
    void handleBallMovement( Time delta );

    void handleBallCollWindow( Ball& ball );

    Ball createNewBall();

    void centerBallOnPlayer( Ball& ball );

private:
    const float m_defBallRadius = 6.0;
    const float m_defBallVelocity = 400.0;

private:
    Game& m_game;

    Player m_player;

    std::vector<Brick> m_bricks;
    std::vector<Ball> m_balls;

    Ball m_ballToFire;
    bool m_hasBallToFire;
};

} // namespace bb
