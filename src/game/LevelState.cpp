#include "LevelState.hpp"

#include <Macros.hpp>
#include <Keyboard.hpp>

namespace bb {

LevelState::LevelState( Game& game )
: m_game( game )
{}

void LevelState::init() {
    setupPlayer();
    setupGrid();
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
}

/* Private */

void LevelState::setupGrid() {

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
