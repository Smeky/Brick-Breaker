#pragma once

#include <Renderer.hpp>

namespace bb {

class Drawable {;
public:
    virtual ~Drawable() {};

    virtual void draw( Renderer& renderer, RenderStates states ) const = 0;
};

} // namespace bb
