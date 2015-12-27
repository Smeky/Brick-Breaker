#pragma once

#include <Vector2.hpp>
#include <Color.hpp>

namespace bb {

struct Vertex {
    Vertex() {}
    Vertex( const Vec2f& _pos, const Color& _color, const Vec2f& _texCoord )
    : pos( _pos )
    , color( _color )
    , texCoord( _texCoord )
    {}

    Vec2f pos;
    Color color;
    Vec2f texCoord;
};

} // namespace bb
