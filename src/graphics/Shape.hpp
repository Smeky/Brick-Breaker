#pragma once

#include <Drawable.hpp>
#include <Transformable.hpp>

namespace bb {

class Shape : public Drawable, public Transformable {
public:
    Shape();

    virtual void draw( Renderer& renderer, RenderStates states ) const;

protected:
    VertexArray m_vertices;

private:


};

} // namespace bb
