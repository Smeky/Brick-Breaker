#include "Texture.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

#include <Macros.hpp>

namespace bb {

Texture::Texture()
: m_handle( 0 )
{}

Texture::~Texture() {
    if( m_handle != 0 ) {
        glDeleteTextures( 1, &m_handle );
    }
}

bool Texture::loadFromFile( const std::string& filename ) {
    // Load file surface
    SDL_Surface* surface = IMG_Load( filename.c_str() );

    // Check for errors
    if( !surface ) {
        ERROR_PRINT( SDL_GetError() );

        return false;
    }

    // Store size of the texture
    m_size.w = surface->w;
    m_size.h = surface->h;

    // If texture was not generated yet
    if( m_handle == 0 ) {
        // Generate texture in OpeGL
        glGenTextures( 1, &m_handle );
    }

    glBindTexture( GL_TEXTURE_2D, m_handle );

    // Setup texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Setup texture data
    glTexImage2D( GL_TEXTURE_2D,
                  0,
                  GL_RGBA,
                  m_size.w,
                  m_size.h,
                  0,
                  GL_RGB,
                  GL_UNSIGNED_BYTE,
                  surface->pixels );

    // Unbind the texture
    glBindTexture( GL_TEXTURE_2D, 0 );

    // Destroy the surface
    SDL_FreeSurface( surface );

    return true;
}

void Texture::bind() {
    if( m_handle != 0 ) {
        glBindTexture( GL_TEXTURE_2D, m_handle );
    }
}

} // namespace bb
