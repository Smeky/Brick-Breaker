#include "Renderer.hpp"

#include <GL/glew.h>

namespace bb {

Renderer::Renderer()
: m_defShader( nullptr )
, m_vbo( 0 )
, m_vao( 0 )
, m_defMaxVertexCount( 32 )
, m_maxVertexCount( m_defMaxVertexCount )
{}

bool Renderer::init() {
    m_vertexCache.resize( m_maxVertexCount );

    glGenBuffers( 1, &m_vbo );
    glGenVertexArrays( 1, &m_vao );

    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER,
                  m_vertexCache.size() * sizeof( Vertex ),
                  m_vertexCache.data(),
                  GL_DYNAMIC_DRAW );

    glBindVertexArray( m_vao );

    glEnableVertexAttribArray( 0 ); // Position
    glEnableVertexAttribArray( 1 ); // Color
    glEnableVertexAttribArray( 2 ); // TexCoord

    glVertexAttribPointer( 0,
                           2,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof( Vertex ),
                           nullptr );

    glVertexAttribPointer( 1,
                           4,
                           GL_UNSIGNED_BYTE,
                           GL_TRUE,
                           sizeof( Vertex ),
                           (const GLvoid*)( sizeof( Vec2f ) ) );

    glVertexAttribPointer( 2,
                           2,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof( Vertex ),
                           (const GLvoid*)( sizeof( Vec2f ) + sizeof( Color ) ) );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    m_defShader = new Shader();
    m_defShader->loadFromFile( Shader::Vertex, "data/shaders/default.vert" );
    m_defShader->loadFromFile( Shader::Fragment, "data/shaders/default.frag" );
    m_defShader->bindAttribute( 0, "a_position" );
    m_defShader->bindAttribute( 1, "a_color" );
    m_defShader->bindAttribute( 2, "a_texCoords" );
    m_defShader->link();

    return true;
}

void Renderer::close() {
    if( m_defShader ) {
        delete m_defShader;
        m_defShader = nullptr;
    }
}

void Renderer::draw( const VertexArray& vertices, const RenderStates& states ) const {
    // Nothing to draw
    if( vertices.size() == 0 ) {
        return;
    }

    Shader* shader = states.shader;
    if( !shader ) {
        shader = m_defShader;
    }

    for( uint32_t i = 0; i < vertices.size(); i++ ) {
        m_vertexCache[ i ] = vertices[ i ];
    }

    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferSubData( GL_ARRAY_BUFFER,
                     0,
                     m_vertexCache.size() * sizeof( Vertex ),
                     m_vertexCache.data() );

    glBindVertexArray( m_vao );



//    glVertexAttribPointer( 0,
//                           2,
//                           GL_FLOAT,
//                           GL_FALSE,
//                           sizeof( Vertex ),
//                           nullptr );
//
//    glVertexAttribPointer( 1,
//                           4,
//                           GL_UNSIGNED_BYTE,
//                           GL_TRUE,
//                           sizeof( Vertex ),
//                           (const GLvoid*)( sizeof( Vec2f ) ) );
//
//    glVertexAttribPointer( 2,
//                           2,
//                           GL_FLOAT,
//                           GL_FALSE,
//                           sizeof( Vertex ),
//                           (const GLvoid*)( sizeof( Vec2f ) + sizeof( Color ) ) );

    shader->use();
    shader->setUniform( "u_model", states.transform );
    shader->setUniform( "u_projection", ortho( 0, 1024, 576, 0 ) );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() );

    shader->stopUsing();
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

//uint32_t Renderer::createVAO( uint32_t size, const Vertex* vertices ) {
//    GLuint vbo;
//    GLuint vao;
//
//    glGenVertexArrays( 1, &vao );
//    glGenBuffers( 1, &vbo );
//
//    glBindBuffer( GL_ARRAY_BUFFER, vbo );
//    glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
//
//    glBindVertexArray( vao );
//
//    glEnableVertexAttribArray( 0 ); // Position
//    glEnableVertexAttribArray( 1 ); // Color
//    glEnableVertexAttribArray( 2 ); // TexCoord
//
//    glVertexAttribPointer( 0,
//                           2,
//                           GL_FLOAT,
//                           GL_FALSE,
//                           sizeof( Vertex ),
//                           nullptr );
//
//    glVertexAttribPointer( 1,
//                           4,
//                           GL_UNSIGNED_BYTE,
//                           GL_TRUE,
//                           sizeof( Vertex ),
//                           (const GLvoid*)( sizeof( Vec2f ) ) );
//
//    glVertexAttribPointer( 2,
//                           2,
//                           GL_FLOAT,
//                           GL_FALSE,
//                           sizeof( Vertex ),
//                           (const GLvoid*)( sizeof( Vec2f ) + sizeof( Color ) ) );
//
//    glBindBuffer( GL_ARRAY_BUFFER, 0 );
//    glBindVertexArray( 0 );
//
//    return vao;
//}

} // namespace bb
