#include "Sprite.hpp"

#include <GL/glew.h>
#include <Vertex.hpp>

namespace bb {

Sprite::Sprite()
{
    m_vertices.resize( 6 );
    m_vertices[ 0 ] = Vertex( Vec2f( 0.0, 1.0 ), Color::White, Vec2f() );
    m_vertices[ 1 ] = Vertex( Vec2f( 1.0, 0.0 ), Color::White, Vec2f() );
    m_vertices[ 2 ] = Vertex( Vec2f( 0.0, 0.0 ), Color::White, Vec2f() );
    m_vertices[ 3 ] = Vertex( Vec2f( 0.0, 1.0 ), Color::White, Vec2f() );
    m_vertices[ 4 ] = Vertex( Vec2f( 1.0, 1.0 ), Color::White, Vec2f() );
    m_vertices[ 5 ] = Vertex( Vec2f( 1.0, 0.0 ), Color::White, Vec2f() );
}

void Sprite::draw( Renderer& renderer, RenderStates states ) const {
    states.transform *= getMatrix();

    renderer.draw( m_vertices, states );
}

} // namespace bb
