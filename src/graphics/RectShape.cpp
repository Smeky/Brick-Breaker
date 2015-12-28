#include "RectShape.hpp"

namespace bb {

RectShape::RectShape()
{
    m_vertices.resize( 4 );
    m_vertices[ 0 ] = Vertex( Vec2f( 0.0, 0.0 ), Color::White, Vec2f() );
    m_vertices[ 1 ] = Vertex( Vec2f( 1.0, 0.0 ), Color::White, Vec2f() );
    m_vertices[ 2 ] = Vertex( Vec2f( 1.0, 1.0 ), Color::White, Vec2f() );
    m_vertices[ 3 ] = Vertex( Vec2f( 0.0, 1.0 ), Color::White, Vec2f() );

    m_vertices.setPrimitiveType( PrimitiveType::PType_Quads );
}

} // namespace bb
