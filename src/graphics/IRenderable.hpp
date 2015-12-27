#pragma once

#include <Renderer.hpp>

namespace bb {

class IRenderable {
public:
    virtual ~IRenderable() {};

    virtual void render( Renderer& renderer, RenderStates states ) const = 0;
};

} // namespace bb
