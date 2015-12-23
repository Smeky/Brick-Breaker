#pragma once

#include <stdint.h>
#include <iostream>

namespace bb {

struct Color {
    union {
        uint8_t data[ 4 ];
        struct { uint8_t r, g, b, a; };
    };

    Color();
    Color( uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255 );
    Color( uint8_t color, uint8_t alpha = 255 );


    static const Color Transparent;
    static const Color White;
    static const Color Black;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Orange;
};

bool operator==( const Color& left, const Color& right );
bool operator!=( const Color& left, const Color& right );
Color operator+( const Color& left, const Color& right );
Color operator-( const Color& left, const Color& right );
Color operator*( const Color& left, const Color& right );
Color operator+=( Color& left, const Color& right );
Color operator-=( Color& left, const Color& right );
Color operator*=( Color& left, const Color& right );
std::ostream& operator<<( std::ostream& os, const Color& color );

} // namespace bb
