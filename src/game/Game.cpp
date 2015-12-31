#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <Macros.hpp>
#include <LevelState.hpp>
#include <CircleShape.hpp>

namespace bb {

const int wWindow = 1024;
const int hWindow = 576;

const float timeStep = 1.0 / 60;

Game::Game()
: m_window( nullptr )
, m_running( false )
, m_timeAccumulator( 0 )
, m_gameState( nullptr )
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

    if( SDL_GL_SetSwapInterval( -1 ) < 0 ) {
        if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
            ERROR_PRINT( "Failed to enable VSync" );
        }
    }

    if( !m_renderer.init() ) {
        ERROR_PRINT( "Renderer failed to init" );
        return false;
    }

    m_runClock.restart();

    m_gameState = new LevelState( *this );
    m_gameState->init();

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

Vec2i Game::getWindowSize() const {
    Vec2i size;

    SDL_GetWindowSize( m_window, &size.x, &size.y );

    return size;
}

/* Private */

void Game::onClose() {
    if( m_gameState ) {
        m_gameState->close();

        delete m_gameState;
    }

    m_renderer.close();

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

        if( m_gameState ) {
            m_gameState->handleInput( event );
        }
    }
}

void Game::update() {
//    m_timeAccumulator += m_runClock.restart().seconds;
//
//    while( m_timeAccumulator >= timeStep ) {
//        m_timeAccumulator -= timeStep;

//        Time delta = timeStep;
        Time delta = m_runClock.restart() ;

        if( m_gameState ) {
            m_gameState->update( delta );
        }
//    }
}

void Game::render() {
    glClearColor( 0.1, 0.1, 0.1, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    RenderStates defRenderStates;

    if( m_gameState ) {
        m_gameState->render( m_renderer, defRenderStates );
    }

    SDL_GL_SwapWindow( m_window );
}

} // namespace bb
