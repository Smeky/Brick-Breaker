#pragma once

#include <IGameState.hpp>

namespace bb {

class LevelState : public IGameState {
public:
    LevelState();

    void init();
    void close();

    void handleInput( SDL_Event event );
    void update( Time delta );
    void render( Renderer& renderer, RenderStates states ) const;

private:



};

} // namespace bb
