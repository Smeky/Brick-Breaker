#include "LevelState.hpp"

#include <Macros.hpp>

namespace bb {

LevelState::LevelState()
{}

void LevelState::init() {
    std::cout << "Init test" << std::endl;
}

void LevelState::close() {
    std::cout << "Close test" << std::endl;
}

void LevelState::handleInput( SDL_Event event ) {

}

void LevelState::update( Time delta ) {

}

void LevelState::render( Renderer& renderer, RenderStates states ) const {

}


} // namespace bb
