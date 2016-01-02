#pragma once

#include <IGameState.hpp>
#include <Game.hpp>
#include <Player.hpp>
#include <Brick.hpp>
#include <Ball.hpp>
#include <Powerup.hpp>
#include <PowerupEffect.hpp>

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

    void restartLevel();

    void givePlayerNewBall();
    void firePlayerBall();

    void handlePlayerMovement( Time delta );
    void handleBallMovement( Time delta );
    void handlePowerupMovement( Time delta );

    void updatePowerupEffects( Time delta );

    void handleBallCollPlayer( Ball& ball );
    // Returns true if ball went outside of level ( screen bottom )
    bool handleBallCollWindow( Ball& ball );
    void handleBallCollBricks( Ball& ball );

    Ball createNewBall();

    void centerBallOnPlayer( Ball& ball );

    void handleOutsideBall();
    void handlePowerupSpawn( const Brick& brick );

    bool isPUEffectActive( Powerup::Type type ) const;

private:
    const float m_defBallRadius = 5.0;
    const float m_defBallVelocity = 300.0;
    const float m_defPowerupVelocity = 300.0;

private:
    Game& m_game;

    Player m_player;

    std::vector<Brick> m_bricks;
    std::vector<Ball> m_balls;
    std::vector<Powerup> m_powerups;
    std::vector<PowerupEffect> m_puEffects;

    Ball m_ballToFire;
    bool m_hasBallToFire;
};

} // namespace bb
