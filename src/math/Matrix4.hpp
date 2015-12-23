#pragma once

#include <Vector3.hpp>
#include <Vector4.hpp>
#include <array>
#include <iostream>

namespace bb {

struct Matrix4 {
    Vec4f data[ 4 ];

    Matrix4()
    : data( {
                { 1, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 0, 1, 0 },
                { 0, 0, 0, 1 },
              }
            )
    {}
    Matrix4( float x )
    : data( {
                { x, 0, 0, 0 },
                { 0, x, 0, 0 },
                { 0, 0, x, 0 },
                { 0, 0, 0, x },
              }
            )
    {}
    Matrix4( const Vec4f& v0, const Vec4f& v1, const Vec4f& v2, const Vec4f& v3 )
    : data( { v0, v1, v2, v3 } )
    {}

    Vec4f& operator[]( uint8_t index ) { return data[ index ]; }
    const Vec4f& operator[]( uint8_t index ) const { return data[ index ]; }

    // Note: GG said that there might be some rare issues with this approach
    bool operator==( const Matrix4& other ) const {
        for( uint8_t i = 0; i < 4; i++ ) {
            if( data[ i ] != other[ i ] ) {
                return false;
            }
        }

        return true;
    }

    bool operator!=( const Matrix4& other ) const {
        return !operator==( other );
    }

    Matrix4 operator+( const Matrix4& other ) const {
        Matrix4 m;

        for( uint8_t i = 0; i < 4; i++ ) {
            m[ i ] = data[ i ] + other[ i ];
        }

        return m;
    }
    Matrix4& operator+=( const Matrix4& other ) {
        return ( *this = (*this) + other );
    }

    Matrix4 operator-( const Matrix4& other ) const {
        Matrix4 m;

        for( uint8_t i = 0; i < 4; i++ ) {
            m[ i ] = data[ i ] - other[ i ];
        }

        return m;
    }
    Matrix4& operator-=( const Matrix4& other ) {
        return ( *this = (*this) - other );
    }

    Matrix4 operator*( const Matrix4& other ) const {
        const Vec4f srcA0 = data[ 0 ];
        const Vec4f srcA1 = data[ 1 ];
        const Vec4f srcA2 = data[ 2 ];
        const Vec4f srcA3 = data[ 3 ];

        const Vec4f srcB0 = other[ 0 ];
        const Vec4f srcB1 = other[ 1 ];
        const Vec4f srcB2 = other[ 2 ];
        const Vec4f srcB3 = other[ 3 ];

        Matrix4 result;

        result[ 0 ] = srcA0 * srcB0[ 0 ] +
                      srcA1 * srcB0[ 1 ] +
                      srcA2 * srcB0[ 2 ] +
                      srcA3 * srcB0[ 3 ];

        result[ 1 ] = srcA0 * srcB1[ 0 ] +
                      srcA1 * srcB1[ 1 ] +
                      srcA2 * srcB1[ 2 ] +
                      srcA3 * srcB1[ 3 ];

        result[ 2 ] = srcA0 * srcB2[ 0 ] +
                      srcA1 * srcB2[ 1 ] +
                      srcA2 * srcB2[ 2 ] +
                      srcA3 * srcB2[ 3 ];

        result[ 3 ] = srcA0 * srcB3[ 0 ] +
                      srcA1 * srcB3[ 1 ] +
                      srcA2 * srcB3[ 2 ] +
                      srcA3 * srcB3[ 3 ];

        return result;
    }
    Matrix4& operator*=( const Matrix4& other ) {
        return ( *this = (*this) * other );
    }

    Vec4f operator*( const Vec4f& v ) const {
        const Vec4f mul0 = data[ 0 ] * v[ 0 ];
        const Vec4f mul1 = data[ 1 ] * v[ 1 ];
        const Vec4f mul2 = data[ 2 ] * v[ 2 ];
        const Vec4f mul3 = data[ 3 ] * v[ 3 ];

        return mul0 + mul1 + mul2 + mul3;
    }

    Matrix4 operator*( float scalar ) const {
        Matrix4 m;

        for( uint8_t i = 0; i < 4; i++ ) {
            m[ i ] = data[ i ] * scalar;
        }

        return m;
    }

    Matrix4 operator/( float scalar ) const {
        Matrix4 m;

        for( uint8_t i = 0; i < 4; i++ ) {
            m[ i ] = data[ i ] / scalar;
        }

        return m;
    }

    /** Methods */

    Matrix4 transpose( const Matrix4& m ) {
        Matrix4 result;

        for( uint8_t i = 0; i < 4; i++ ) {
            for( uint8_t j = 0; j < 4; j++ ) {
                result[ i ][ j ] = m[ j ][ i ];
            }
        }

        return result;
    }
};

// Matrix4 operator*( float scalar, const Matrix4& m ) {
//     return m * scalar;
// }

float determinant( const Matrix4& m );
Matrix4 inverse( const Matrix4& m );
Matrix4 hadamardProduct( const Matrix4& a, const Matrix4& b );

Matrix4 translate( const Vec3f& v );
Matrix4 rotate( float rAngle, const Vec3f& v );
Matrix4 scale( const Vec3f& v );

Matrix4 ortho( float left, float right, float bottom, float top );
Matrix4 ortho( float left, float right, float bottom, float top, float zNear, float zFar );

Matrix4 perspective( float fovy, float aspect, float zNear, float zFar );
Matrix4 infinitePerspective( float fovy, float aspect, float zNear );

Matrix4 lookAt( const Vec3f& position, const Vec3f& center, const Vec3f& up );

std::ostream& operator<<( std::ostream& os, const Matrix4& m );

} // namespace bb
