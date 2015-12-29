#pragma once

#include <IGameState.hpp>
#include <Game.hpp>
#include <Player.hpp>
#include <Brick.hpp>

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

    void handlePlayerMovement( Time delta );

private:
    Game& m_game;

    Player m_player;

    std::vector<Brick> m_bricks;
};

} // namespace bb
