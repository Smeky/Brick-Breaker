#include "Matrix3.hpp"

namespace bb {

Matrix3::Matrix3()
: data( { { 1, 0, 0 },
          { 0, 1, 0 },
          { 0, 0, 1 } } )
{}

Matrix3::Matrix3( float x )
: data( { { x, 0, 0 },
          { 0, x, 0 },
          { 0, 0, x } } )
{}

Matrix3::Matrix3( const Vec3f& v0, const Vec3f& v1, const Vec3f& v2 )
: data( { v0, v1, v2 } )
{}


Vec3f& Matrix3::operator[]( uint8_t index ) {
    return data[ index ];
}

const Vec3f& Matrix3::operator[]( uint8_t index ) const {
    return data[ index ];
}

bool Matrix3::operator==( const Matrix3& other ) const {
    for( uint8_t i = 0; i < 3; i++ ) {
        if( data[ i ] != other[ i ] ) {
            return false;
        }
    }

    return true;
}

bool Matrix3::operator!=( const Matrix3& other ) const {
    return !operator==( other );
}

Matrix3 Matrix3::operator+( const Matrix3& other ) const {
    Matrix3 m;

    for( uint8_t i = 0; i < 3; i++ ) {
        m[ i ] = data[ i ] + other[ i ];
    }

    return m;
}

Matrix3 Matrix3::operator-( const Matrix3& other ) const {
    Matrix3 m;

    for( uint8_t i = 0; i < 3; i++ ) {
        m[ i ] = data[ i ] - other[ i ];
    }

    return m;
}

Matrix3 Matrix3::operator*( const Matrix3& other ) const {
        const Vec3f srcA0 = data[ 0 ];
        const Vec3f srcA1 = data[ 1 ];
        const Vec3f srcA2 = data[ 2 ];

        const Vec3f srcB0 = other[ 0 ];
        const Vec3f srcB1 = other[ 1 ];
        const Vec3f srcB2 = other[ 2 ];

        Matrix3 result;

        result[ 0 ] = srcA0 * srcB0[ 0 ] +
                      srcA1 * srcB0[ 1 ] +
                      srcA2 * srcB0[ 2 ];

        result[ 1 ] = srcA0 * srcB1[ 0 ] +
                      srcA1 * srcB1[ 1 ] +
                      srcA2 * srcB1[ 2 ];

        result[ 2 ] = srcA0 * srcB2[ 0 ] +
                      srcA1 * srcB2[ 1 ] +
                      srcA2 * srcB2[ 2 ];

        return result;
}

Matrix3& Matrix3::operator+=( const Matrix3& other ) {
    return ( *this = (*this) + other );
}

Matrix3& Matrix3::operator-=( const Matrix3& other ) {
    return ( *this = (*this) - other );
}

Matrix3& Matrix3::operator*=( const Matrix3& other ) {
    return ( *this = (*this) * other );
}

Matrix3 Matrix3::operator*( float scalar ) const {
    Matrix3 m;

    for( uint8_t i = 0; i < 3; i++ ) {
        m[ i ] = data[ i ] * scalar;
    }

    return m;
}

Matrix3 Matrix3::operator/( float scalar ) const {
    Matrix3 m;

    for( uint8_t i = 0; i < 3; i++ ) {
        m[ i ] = data[ i ] / scalar;
    }

    return m;
}

} // namespace bb
