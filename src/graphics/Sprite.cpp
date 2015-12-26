#include "Sprite.hpp"

#include <GL/glew.h>

// Temporary
#include <game/Game.hpp>

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

        glBindVertexArray( s_spriteVAO );
        glDrawArrays( GL_TRIANGLES, 0, 6 );
        glBindVertexArray( 0 );

        shader->stopUsing();
    }
}

void Sprite::createSpriteVAO() {
    const float vertices[] = {
    //  x,   y,   r,   g,   b,   a
        0.0, 1.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 0
        1.0, 0.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 1
        0.0, 0.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 2

        0.0, 1.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 0
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 2
        1.0, 0.0, 1.0, 1.0, 1.0, 1.0,   // Vertex 3
    };

    GLuint vbo;

    glGenVertexArrays( 1, &s_spriteVAO );
    glGenBuffers( 1, &vbo );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindVertexArray( s_spriteVAO );

    glEnableVertexAttribArray( 0 ); // Position
    glEnableVertexAttribArray( 1 ); // Color

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), nullptr );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), (const GLvoid*)( 2 * sizeof( float ) ) );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );
}

} // namespace bb
