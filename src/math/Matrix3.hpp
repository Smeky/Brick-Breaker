#pragma once

#include <Vector3.hpp>
#include <ostream>

namespace bb {

struct Matrix3 {
    Vec3f data[ 3 ];

    Matrix3();
    Matrix3( float x );
    Matrix3( const Vec3f& v0, const Vec3f& v1, const Vec3f& v2 );

    Vec3f& operator[]( uint8_t index );
    const Vec3f& operator[]( uint8_t index ) const;

    bool operator==( const Matrix3& other ) const;
    bool operator!=( const Matrix3& other ) const;

    Matrix3 operator+( const Matrix3& other ) const;
    Matrix3 operator-( const Matrix3& other ) const;
    Matrix3 operator*( const Matrix3& other ) const;
    Matrix3& operator+=( const Matrix3& other );
    Matrix3& operator-=( const Matrix3& other );
    Matrix3& operator*=( const Matrix3& other );

    Matrix3 operator*( float scalar ) const;
    Matrix3 operator/( float scalar ) const;
};

std::ostream& operator<<( std::ostream& os, const Matrix3& m );

} // namespace bb
