#pragma once

#include <SDL_events.h>
#include <Time.hpp>
#include <Renderer.hpp>
#include <RenderStates.hpp>

namespace bb {

class IGameState {
public:
    virtual ~IGameState() {}

    virtual void init() = 0;
    virtual void close() = 0;

    virtual void handleInput( SDL_Event event ) = 0;
    virtual void update( Time delta ) = 0;
    virtual void render( Renderer& renderer, RenderStates states ) const = 0;
};

} // namespace bb
