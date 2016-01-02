#include "LevelState.hpp"

#include <Macros.hpp>
#include <Keyboard.hpp>

#include <cmath>

const float PI = 3.14159265;

namespace bb {

float clamp( float value, float min, float max ) {
    return std::max( min, std::min( max, value ) );
}

Vec2f clamp( const Vec2f& value, const Vec2f& min, const Vec2f& max ) {
    return Vec2f( clamp( value.x, min.x, max.x ),
                  clamp( value.y, min.y, max.y ) );
}

enum Direction {
    Dir_Up,
    Dir_Right,
    Dir_Down,
    Dir_Left
};

Direction vectorDirection( const Vec2f& target ) {
    static const Vec2f compass[] = {
        Vec2f(  0.0,  1.0 ),
        Vec2f(  1.0,  0.0 ),
        Vec2f(  0.0, -1.0 ),
        Vec2f( -1.0,  0.0 ),
    };

    float max = 0.0;
    int bestMatch = -1;

    for( int i = 0; i < 4; i++ ) {
        float dotProduct = dot( normalized( target ), compass[ i ] );

        if( dotProduct > max ) {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return (Direction)bestMatch;
}

bool checkCollision( const CircleShape& circle,
                     const Brick& brick,
                     Direction& dir )
{
    Vec2f ballCenter = circle.getPos() + circle.getRadius();

    Vec2f aabbHalfExtent = brick.getSize() / 2;
    Vec2f aabbCenter = brick.getPos() + aabbHalfExtent;

    Vec2f difference = ballCenter - aabbCenter;
    Vec2f clamped = clamp( difference, - aabbHalfExtent, aabbHalfExtent );
    Vec2f closest = aabbCenter + clamped;

    float distance = lenght( closest - ballCenter );

    if( distance < circle.getRadius() ) {
        dir = vectorDirection( difference );

        Vec2f brickCenter = brick.getPos() + brick.getSize() / 2;
        Vec2f circCenter = circle.getPos() + circle.getRadius();

        const float* cornerAngles = brick.getCornerAngles();

        // Rect center to ball center
        float cc = angle( brickCenter, circCenter );

        // Get collision side based on ball-to-brick angle
        if(      cc >= cornerAngles[ 0 ] && cc <= cornerAngles[ 1 ] ) dir = Direction::Dir_Up;
        else if( cc >= cornerAngles[ 1 ] && cc <= cornerAngles[ 2 ] ) dir = Direction::Dir_Right;
        else if( cc >= cornerAngles[ 2 ] && cc <= cornerAngles[ 3 ] ) dir = Direction::Dir_Down;
        else if( cc >= cornerAngles[ 3 ] && cc <= cornerAngles[ 0 ] ) dir = Direction::Dir_Left;

        return true;
    }
    else {
        return false;
    }
}

bool checkCollision( const RectShape& a, const RectShape& b ) {
    const Vec2f aPos = a.getPos();
    const Vec2f aSize = a.getSize();

    const Vec2f bPos = b.getPos();
    const Vec2f bSize = b.getSize();

    if(      aPos.x > bPos.x + bSize.w ) return false;
    else if( aPos.x + aSize.w < bPos.x ) return false;
    else if( aPos.y > bPos.y + bSize.h ) return false;
    else if( aPos.y + aSize.h < bPos.y ) return false;

    return true;
}

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
        else if( event.key.keysym.sym == SDLK_r ) {
            restartLevel();
        }
    }
}

void LevelState::update( Time delta ) {
    handlePlayerMovement( delta );
    handleBallMovement( delta );
    handlePowerupMovement( delta );
}

void LevelState::render( Renderer& renderer, RenderStates states ) const {
    for( const Brick& brick : m_bricks ) {
        renderer.draw( brick, states );
    }

    for( const Powerup& powerup : m_powerups ) {
        renderer.draw( powerup, states );
    }

    for( const Ball& ball : m_balls ) {
        renderer.draw( ball, states );
    }

    if( m_hasBallToFire ) {
        renderer.draw( m_ballToFire, states );
    }

    renderer.draw( m_player, states );
}

/* Private */

void LevelState::setupPlayer() {
    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f playerSize = Vec2f( 120, 7 );

    m_player.setSize( playerSize );
    m_player.setPos( ( windowSize.x - playerSize.x ) / 2,
                     windowSize.y - playerSize.y - 4 );

    m_player.setColor( Color::Red );
    m_player.setVelocity( 300 );
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
            brick.updateCornerAngles();

            size_t index = y * width + x;
            m_bricks[ index ] = brick;
        }
    }
}

void LevelState::restartLevel() {
    m_balls.clear();

    setupPlayer();
    setupBricks();

    givePlayerNewBall();
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
    const Vec2f playerCenter = m_player.getPos() + m_player.getSize() / 2;
    const Vec2i windowSize = m_game.getWindowSize();

    // Calculate fire angle based on players position
    const float factor = playerCenter.x / windowSize.x;
    const float angle = factor * PI + PI;
    const float velocity = m_ballToFire.getVelocity();

    m_ballToFire.setDirVelocity( Vec2f( velocity * std::cos( angle ),
                                        velocity * std::sin( angle ) ) );

    // Fire the ball
    m_balls.push_back( m_ballToFire );
    m_hasBallToFire = false;

    givePlayerNewBall();


//    const float PI = 3.14159265;
//
//    // Calculate fire angle based on players position
//    for( float  i = 0; i < 9; i++ ) {
//        const float factor = ( 1 + i ) / 10;
//        const float angle = factor * PI + PI;
//        const float velocity = m_ballToFire.getVelocity();
//
//        m_ballToFire.setDirVelocity( Vec2f( velocity * std::cos( angle ),
//                                            velocity * std::sin( angle ) ) );
//
//        // Fire the ball
//        m_balls.push_back( m_ballToFire );
//    }
//
//    m_hasBallToFire = false;
//
//    givePlayerNewBall();
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
    for( auto it = m_balls.begin(); it != m_balls.end(); ) {
        Ball& ball = *it;

        ball.move( ball.getDirVelocity() * delta.seconds );

        if( handleBallCollWindow( ball ) ) {
            handleOutsideBall();

            // Replace the ball with last one
            ball = m_balls.back();
            m_balls.pop_back();
        }
        else {
            handleBallCollPlayer( ball );
            handleBallCollBricks( ball );

            it++;
        }
    }
}

void LevelState::handlePowerupMovement( Time delta ) {
    for( auto it = m_powerups.begin(); it != m_powerups.end(); ) {
        Powerup& powerup = *it;

        powerup.move( 0, m_defPowerupVelocity * delta.seconds );

        if( checkCollision( powerup, m_player ) ) {
            // Todo: add powerup buff

            // Replace powerup by last one
            powerup = m_powerups.back();
            m_powerups.pop_back();
        }
        else {
            it++;
        }
    }
}

bool LevelState::handleBallCollWindow( Ball& ball ) {
    const Vec2i windowSize = m_game.getWindowSize();
    const Vec2f ballPos = ball.getPos();
    const float ballSize = ball.getRadius() * 2;
    const Vec2f ballVel = ball.getDirVelocity();

    // X-Axis
    if( ballPos.x < 0 ) {
        ball.setPos( 0, ballPos.y );
        ball.setDirVelocity( Vec2f( - ballVel.x, ballVel.y ) );
    }
    else if( ballPos.x + ballSize > windowSize.x ) {
        ball.setPos( windowSize.x - ballSize, ballPos.y );
        ball.setDirVelocity( Vec2f( - ballVel.x, ballVel.y ) );
    }

    // Y-Axis
    if( ballPos.y < 0 ) {
        ball.setPos( ballPos.x, 0 );
        ball.setDirVelocity( Vec2f( ballVel.x, - ballVel.y ) );
    }
    else if( ballPos.y > windowSize.y + ball.getRadius() ) {
        return true;
    }

    return false;
}

void LevelState::handleBallCollPlayer( Ball& ball ) {
    const Vec2f playerSize = m_player.getSize();
    const Vec2f ballCenter = ball.getPos() + ball.getRadius() - m_player.getPos();

    // If ball is in player's Y-axis
    if( ball.getPos().y + ball.getRadius() * 2 >= m_player.getPos().y ) {
        // If ball collided with player
        if( ballCenter.x >= 0 && ballCenter.x <= playerSize.x ) {
            const float offset = playerSize.x / 12;

            const float factor = ( offset + ballCenter.x ) / ( playerSize.x + offset * 2 );
            const float angle = factor * PI + PI;
            const float velocity = ball.getVelocity();

            ball.setDirVelocity( Vec2f( velocity * std::cos( angle ),
                                        velocity * std::sin( angle ) ) );
        }
    }
}

void LevelState::handleBallCollBricks( Ball& ball ) {
    Direction dir;

    Vec2f ballVelocity = ball.getDirVelocity();

    for( auto it = m_bricks.begin(); it != m_bricks.end(); it++ ) {
        Brick& brick = *it;

        // Check for collision
        if( checkCollision( ball, brick, dir ) ) {
            handlePowerupSpawn( brick );

            // Direction of collision
            if( dir == Dir_Left || dir == Dir_Right ) {
                // Reverse direction of movement
                ballVelocity.x = -ballVelocity.x;
                ball.setDirVelocity( ballVelocity );

//                // Calculate by how much did the ball exceed brick's border
//                float penetration = ball.getRadius() - std::abs( diffVector.x );
//
//                // Move back based on collision direction
//                if( dir == Dir_Left ) {
//                    ball.move( penetration, 0 );
//                }
//                else {
//                    ball.move( -penetration, 0 );
//                }
            }
            else {
                // Reverse direction of movement
                ballVelocity.y = -ballVelocity.y;
                ball.setDirVelocity( ballVelocity );

//                // Calculate by how much did the ball exceed brick's border
//                float penetration = ball.getRadius() - std::abs( diffVector.y );
//
//                // Move back based on collision direction
//                if( dir == Dir_Up ) {
//                    ball.move( 0, -penetration );
//                }
//                else {
//                    ball.move( 0, +penetration );
//                }
            }

            brick = m_bricks.back();
            m_bricks.pop_back();
            break;
        }
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
    const float factor = ( playerPos.x + playerSize.x / 2 ) / windowSize.x;

    const float xCenter = playerPos.x + playerSize.x * factor;
    const float ballRad = ball.getRadius();

    ball.setPos( xCenter - ballRad, playerPos.y - ballRad * 2 );
}

void LevelState::handleOutsideBall() {
    // Remove health, etc.
}

void LevelState::handlePowerupSpawn( const Brick& brick ) {
    static const Powerup::Type types[] = {
        Powerup::AddBall,
        Powerup::Speedup,
        Powerup::Slow,
        Powerup::PaddleGrow,
        Powerup::PaddleShrink,
        Powerup::Damage,
        Powerup::Chaos,
    };

    // Todo: Roll a chance to spawn powerup and choose random powerup

    Powerup powerup;
    powerup.setSize( 30 );
    powerup.setCenter( brick.getCenter() );
    powerup.setColor( Color::Orange );

    m_powerups.push_back( powerup );
}

} // namespace bb


