#include <Game.hpp>
#include <Macros.hpp>

int main( int argc, char* argv[] ) {
    bb::Game game;

    if( !game.init() ) {
        ERROR_PRINT( "Game init failed" );
        return 1;
    }

    game.run();

    return 0;
}
