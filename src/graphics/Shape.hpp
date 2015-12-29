#pragma once

#include <Drawable.hpp>
#include <Transformable.hpp>

namespace bb {

class Shape : public Drawable, public Transformable {
public:
    Shape();

    virtual void draw( const Renderer& renderer, RenderStates states ) const;

    void setColor( const Color& color );
    const Color& getColor() const;

    VertexArray& getVertices();

protected:
    VertexArray m_vertices;
    Color m_color;


};

} // namespace bb
