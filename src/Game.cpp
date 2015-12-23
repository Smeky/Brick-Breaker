#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <Macros.hpp>

namespace bb {

SDL_Window* Game::m_window = nullptr;
bool Game::m_running = false;

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
                                 1024, 576,
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

    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        ERROR_PRINT( "Failed to enable VSync" );
    }

    float vertices[] = {
        // x    y
        +0.0, -0.5,
        +0.5, +0.5,
        -0.5, +0.5
    };

    GLuint vbo;
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

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

    SDL_GL_SwapWindow( m_window );
}

} // namespace bb
