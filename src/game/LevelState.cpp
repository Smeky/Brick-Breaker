#include "LevelState.hpp"

#include <Macros.hpp>
#include <Keyboard.hpp>

#include <cmath>

namespace bb {

LevelState::LevelState( Game& game )
: m_game( game )
, m_hasBallToFire( false )
{}

void LevelState::init() {
    setupPlayer();
    setupBricks();

    givePlayerNewBall();
}

void LevelState::close() {

}

void LevelState::handleInput( SDL_Event event ) {
    if( event.type == SDL_KEYUP ) {
        if( event.key.keysym.sym == SDLK_SPACE ) {
            if( m_hasBallToFire ) {
                firePlayerBall();
            }
        }
    }
}

void LevelState::update( Time delta ) {
    handlePlayerMovement( delta );
    handleBallMovement( delta );
}

void LevelState::render( Renderer& renderer, RenderStates states ) const {
    renderer.draw( m_player, states );

    for( const Brick& brick : m_bricks ) {
        renderer.draw( brick, states );
    }

    for( const Ball& ball : m_balls ) {
        renderer.draw( ball, states );
    }

    if( m_hasBallToFire ) {
        renderer.draw( m_ballToFire, states );
    }
}

/* Private */

void LevelState::setupPlayer() {
    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f playerSize = Vec2f( 120, 12 );

    m_player.setSize( playerSize );
    m_player.setPos( ( windowSize.x - playerSize.x ) / 2,
                     windowSize.y - playerSize.y - 4 );

    m_player.setColor( Color::Red );
    m_player.setVelocity( 1000 );
}

void LevelState::setupBricks() {
    const uint8_t height = 7;
    const uint8_t width = 11;

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
            brick.setColor( Color( 60, 125, 190 ) );
            brick.getVertices()[ 0 ].color = Color( 90, 150, 205 );
            brick.getVertices()[ 2 ].color = Color( 50, 90, 140 );
            brick.getVertices()[ 3 ].color = Color( 50, 90, 140 );

            size_t index = y * width + x;
            m_bricks[ index ] = brick;
        }
    }
}

void LevelState::givePlayerNewBall() {
    // If player already has a ball, don't create new one
    if( m_hasBallToFire ) {
        return;
    }

    Ball ball = createNewBall();

    centerBallOnPlayer( ball );

    m_ballToFire = ball;
    m_hasBallToFire = true;
}

void LevelState::firePlayerBall() {
    const Vec2f playerCenter = m_player.getPos() - m_player.getSize() / 2;
    const Vec2i windowSize = m_game.getWindowSize();

    // Calculate fire angle based on players position
    const float factor = playerCenter.x / windowSize.x;
    const float angle = 180 - factor * 180;
    const float velocity = m_ballToFire.getVelocity();

    m_ballToFire.setDirVelocity( Vec2f( velocity * std::sin( angle ),
                                        velocity * std::cos( angle ) ) );

    // Fire the ball
    m_balls.push_back( m_ballToFire );
    m_hasBallToFire = false;
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

    if( m_hasBallToFire ) {
        centerBallOnPlayer( m_ballToFire );
    }
}

void LevelState::handleBallMovement( Time delta ) {
    for( Ball& ball : m_balls ) {
        ball.move( ball.getDirVelocity() * delta.seconds );

        handleBallCollWindow( ball );
    }
}

void LevelState::handleBallCollWindow( Ball& ball ) {
    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f ballPos = ball.getPos();
    const float ballRadius = ball.getRadius();
    const Vec2f ballVel = ball.getDirVelocity();

    // X-Axis
    if( ballPos.x < 0 ) {
        ball.setPos( 0, ballPos.y );
        ball.setDirVelocity( Vec2f( - ballVel.x, ballVel.y ) );
    }
    else if( ballPos.x + ballRadius > windowSize.x ) {
        ball.setPos( windowSize.x - ballRadius, ballPos.y );
        ball.setDirVelocity( Vec2f( - ballVel.x, ballVel.y ) );
    }

    // Y-Axis
    if( ballPos.y < 0 ) {
        ball.setPos( ballPos.x, 0 );
        ball.setDirVelocity( Vec2f( ballVel.x, - ballVel.y ) );
    }
    else if( ballPos.y + ballRadius > windowSize.y ) {
        ball.setPos( ballPos.x, windowSize.y - ballRadius );
        ball.setDirVelocity( Vec2f( ballVel.x, - ballVel.y ) );
    }
}

Ball LevelState::createNewBall() {
    Ball ball;

    ball.setPointCount( 16 );
    ball.setRadius( m_defBallRadius );
    ball.setColor( Color::Yellow );
    ball.setVelocity( m_defBallVelocity );

    return ball;
}

void LevelState::centerBallOnPlayer( Ball& ball ) {
    const Vec2f playerPos = m_player.getPos();
    const Vec2f playerSize = m_player.getSize();
    const Vec2i windowSize = m_game.getWindowSize();

    const float xCenter = playerPos.x + playerSize.x / 2;
    const float ballRad = ball.getRadius();

    ball.setPos( xCenter - ballRad, playerPos.y - ballRad * 2 );
}

} // namespace bb
