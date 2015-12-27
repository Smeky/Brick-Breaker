#pragma once

#include <Transformable.hpp>
#include <IRenderable.hpp>
#include <VertexArray.hpp>
#include <stdint-gcc.h>

namespace bb {

class Sprite : public IRenderable, public Transformable {
public:
    Sprite();

    void render( Renderer& renderer, RenderStates states ) const;

private:
    VertexArray m_vertices;

};

} // namespace bb
