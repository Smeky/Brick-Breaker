#include "Input.hpp"

#include <SDL_events.h>

namespace bb {

Event::Type getEventTypeFromSDLEvent( SDL_Event event ) {
    Event::Type result = Event::Unknown;

    switch( event.type ) {
    case SDL_EventType::SDL_QUIT:            result = Event::Quit; break;
    case SDL_EventType::SDL_KEYDOWN:         result = Event::KeyDown; break;
    case SDL_EventType::SDL_KEYUP:           result = Event::KeyUp; break;
    case SDL_EventType::SDL_MOUSEBUTTONDOWN: result = Event::MouseButtonDown; break;
    case SDL_EventType::SDL_MOUSEBUTTONUP:   result = Event::MouseButtonUp; break;
    case SDL_EventType::SDL_MOUSEMOTION:     result = Event::MouseMotion; break;
    case SDL_EventType::SDL_MOUSEWHEEL:      result = Event::MouseWheel; break;
    default: break;
    }

    return result;
}

bool pollEvent( Event& event ) {
    SDL_Event sdlEvent;

    // Poll SDL event
    if( !SDL_PollEvent( &sdlEvent ) ) {
        return false;
    }

    // Reset event
    event = Event();

    event.type = getEventTypeFromSDLEvent( sdlEvent );

    return true;
}

} // namespace bb
