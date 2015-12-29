#include "LevelState.hpp"

#include <Macros.hpp>
#include <Keyboard.hpp>

namespace bb {

LevelState::LevelState( Game& game )
: m_game( game )
{}

void LevelState::init() {
    setupPlayer();
    setupBricks();
}

void LevelState::close() {

}

void LevelState::handleInput( SDL_Event event ) {

}

void LevelState::update( Time delta ) {
    handlePlayerMovement( delta );
}

void LevelState::render( Renderer& renderer, RenderStates states ) const {
    renderer.draw( m_player, states );

    for( const Brick& brick : m_bricks ) {
        renderer.draw( brick, states );
    }
}

/* Private */

void LevelState::setupBricks() {
    const uint8_t height = 7;
    const uint8_t width = 13;

    const float brickOffset = 2;

    const Vec2f brickSize = Vec2f( 70, 30 );
    const Vec2f fieldSize = Vec2f( ( brickOffset + brickSize.x ) * width,
                                   ( brickOffset + brickSize.y ) * height );

    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f fieldPos = Vec2f( ( windowSize.x - fieldSize.x ) / 2,
                                  60 );

    m_bricks.resize( height * width );

    for( uint8_t y = 0; y < height; y++ ) {
        for( uint8_t x = 0; x < width; x++ ) {
            Brick brick;

            brick.setSize( brickSize );
            brick.setPos( fieldPos + Vec2i( x, y ) * ( brickSize + brickOffset ) );
            brick.setColor( Color::Orange );
            brick.getVertices()[ 0 ].color = Color::Yellow;

            size_t index = y * width + x;
            m_bricks[ index ] = brick;
        }
    }
}

void LevelState::setupPlayer() {
    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f playerSize = Vec2f( 120, 12 );

    m_player.setSize( playerSize );
    m_player.setPos( ( windowSize.x - playerSize.x ) / 2,
                     windowSize.y - playerSize.y - 4 );

    m_player.setColor( Color::Red );
    m_player.setVelocity( 800 );
}

void LevelState::handlePlayerMovement( Time delta ) {
    const float playerVelocity = m_player.getVelocity();
    float currentVelocity = 0.0;

    // Check for direction input
    if( Keyboard::isPressed( Key::Left ) || Keyboard::isPressed( Key::A ) ) {
        currentVelocity -= playerVelocity;
    }
    if( Keyboard::isPressed( Key::Right ) || Keyboard::isPressed( Key::D ) ) {
        currentVelocity += playerVelocity;
    }

    if( currentVelocity != 0.0 ) {
        // Calculate player movement
        const float moveSpeed = currentVelocity * delta;

        // Move player
        m_player.move( moveSpeed, 0.0 );

        const Vec2f playerSize = m_player.getSize();
        const Vec2f playerPos = m_player.getPos();
        const Vec2i windowSize = m_game.getWindowSize();

        // Check if player went out of window bounds
        if( playerPos.x < 0 ) {
            m_player.setPos( 0, playerPos.y );
        }
        else if( playerPos.x + playerSize.w > windowSize.x ) {
            m_player.setPos( windowSize.x - playerSize.w, playerPos.y );
        }
    }
}

} // namespace bb
