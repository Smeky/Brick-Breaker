#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <Macros.hpp>
#include <Shader.hpp>
#include <Transformable.hpp>

namespace bb {

const int wWindow = 1024;
const int hWindow = 576;

SDL_Window* Game::m_window = nullptr;
bool Game::m_running = false;

Shader* shader = nullptr;

Game::Game()
{}

bool Game::init() {
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
        ERROR_PRINT( SDL_GetError() );
        return false;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    m_window = SDL_CreateWindow( "Brick Breaker",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 wWindow,
                                 hWindow,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
                                );

    if( !m_window ) {
        ERROR_PRINT( SDL_GetError() );
        return false;
    }

    if( !SDL_GL_CreateContext( m_window ) ) {
        ERROR_PRINT( "Failed creating OpenGL context" );
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    if( glewError != GL_NO_ERROR ) {
        ERROR_PRINT( "Glew init failed" );
        return false;
    }

    glViewport( 0, 0, wWindow, hWindow );

    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        ERROR_PRINT( "Failed to enable VSync" );
    }

    shader = new Shader();
    shader->loadFromFile( Shader::Vertex, "data/shaders/default.vert" );
    shader->loadFromFile( Shader::Fragment, "data/shaders/default.frag" );
    shader->bindAttribute( AttribLocation::Position, "position" );
    shader->link();
    shader->use();

    float vertices[] = {
        // x     y
        +0.0, +0.5,
        -0.4, -0.5,
        +0.4, -0.5,
    };

    Transformable t( 10, 20 );
    t.move( 30, 30 );
    std::cout << t.getPos() << std::endl;

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 0,
                           2,
                           GL_FLOAT,
                           GL_FALSE,
                           2 * sizeof( float ),
                           (const GLvoid*)0 );

    return true;
}

void Game::run() {
    m_running = true;

    while( m_running ) {
        handleInput();
        update();
        render();
    }

    onClose();
}

void Game::close() {
    m_running = false;
}

/* Private */

void Game::onClose() {
    SDL_DestroyWindow( m_window );
    SDL_Quit();
}

void Game::handleInput() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
        if( event.type == SDL_QUIT ) {
            close();
        }
        else if( event.type == SDL_KEYDOWN ) {
            if( event.key.keysym.sym == SDLK_ESCAPE ) {
                close();
            }
        }
    }
}

void Game::update() {

}

void Game::render() {
    glClearColor( 0.1, 0.1, 0.1, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );

//    shader.use();



    glDrawArrays( GL_TRIANGLES, 0, 3 );

//    glDisableVertexAttribArray( 0 );

//    shader.stopUsing();

    SDL_GL_SwapWindow( m_window );
}

} // namespace bb
