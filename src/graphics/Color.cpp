#include "Color.hpp"

namespace bb {

const Color Color::Transparent = Color( 255, 0 );
const Color Color::White       = Color( 255 );
const Color Color::Black       = Color( 0 );

const Color Color::Red         = Color( 255, 0, 0 );
const Color Color::Green       = Color( 0, 255, 0 );
const Color Color::Blue        = Color( 0, 0, 255 );
const Color Color::Yellow      = Color( 255, 255, 0 );
const Color Color::Orange      = Color( 255, 153, 0 );

Color::Color()
: r( 0 )
, g( 0 )
, b( 0 )
, a( 255 )
{}

Color::Color( uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a /* = 255 */ )
: r( _r )
, g( _g )
, b( _b )
, a( _a )
{}


Color::Color( uint8_t color, uint8_t alpha /* = 255 */ )
: r( color )
, g( color )
, b( color )
, a( alpha )
{}

} // namespace bb
