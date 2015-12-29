#pragma once

#include <IGameState.hpp>
#include <Game.hpp>
#include <Player.hpp>

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
    void setupGrid();
    void setupPlayer();

    void handlePlayerMovement( Time delta );

private:
    Game& m_game;

    Player m_player;
};

} // namespace bb
