#include "Renderer.hpp"

#include <GL/glew.h>

namespace bb {

Renderer::Renderer()
{}

uint32_t Renderer::createVAO( uint32_t size, const Vertex* vertices ) {
    GLuint vbo;
    GLuint vao;

    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

    glBindVertexArray( vao );

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

    return vao;
}

} // namespace bb
