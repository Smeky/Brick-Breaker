#pragma once

#include <Transformable.hpp>
#include <Drawable.hpp>
#include <VertexArray.hpp>

namespace bb {

class Sprite : public Drawable, public Transformable {
public:
    Sprite();

    void draw( const Renderer& renderer, RenderStates states ) const;

private:
    VertexArray m_vertices;

};

} // namespace bb
