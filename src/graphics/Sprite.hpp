#pragma once

#include <Transformable.hpp>
#include <Drawable.hpp>
#include <VertexArray.hpp>
#include <stdint-gcc.h>

namespace bb {

class Sprite : public Drawable, public Transformable {
public:
    Sprite();

    void draw( Renderer& renderer, RenderStates states ) const;

private:
    VertexArray m_vertices;

};

} // namespace bb
