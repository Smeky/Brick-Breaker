#include "Sprite.hpp"

#include <GL/glew.h>
#include <Vertex.hpp>

// Temporary
#include <game/Game.hpp>
#include <Color.hpp>

namespace bb {

uint32_t Sprite::s_spriteVAO = 0;

Sprite::Sprite()
{}

void Sprite::draw() const {
    if( s_spriteVAO == 0 ) {
        return;
    }

    Shader* shader = Game::shader;

    if( shader ) {
        shader->use();

        shader->setUniform( "u_model", getMatrix() );
        shader->setUniform( "u_projection", ortho( 0, 1024, 576, 0 ) );
        shader->setUniform( "u_color", Color::White );

        glBindVertexArray( s_spriteVAO );
        glDrawArrays( GL_TRIANGLES, 0, 6 );
        glBindVertexArray( 0 );

        shader->stopUsing();
    }
}

void Sprite::createSpriteVAO() {
    const Vertex vertices[] = {
        Vertex( Vec2f( 0.0, 1.0 ), Color::White, Vec2f() ), // Vertex 0
        Vertex( Vec2f( 1.0, 0.0 ), Color::White, Vec2f() ), // Vertex 1
        Vertex( Vec2f( 0.0, 0.0 ), Color::White, Vec2f() ), // Vertex 2

        Vertex( Vec2f( 0.0, 1.0 ), Color::White, Vec2f() ), // Vertex 0
        Vertex( Vec2f( 1.0, 1.0 ), Color::White, Vec2f() ), // Vertex 2
        Vertex( Vec2f( 1.0, 0.0 ), Color::White, Vec2f() ), // Vertex 3
    };

    GLuint vbo;

    glGenVertexArrays( 1, &s_spriteVAO );
    glGenBuffers( 1, &vbo );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindVertexArray( s_spriteVAO );

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
}

} // namespace bb
